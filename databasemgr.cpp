#include <QCoreApplication>
#include <QSqlQuery>
#include <QVariant>
#include <QFile>
#include "databasemgr.h"

//--------------------------------------------------------------------------------------
DatabaseMgr* DatabaseMgr::instance = NULL;

//--------------------------------------------------------------------------------------
DatabaseMgr* DatabaseMgr::Instance()
{
    if(!instance)
        instance = new DatabaseMgr();

    return instance;
}

//--------------------------------------------------------------------------------------
QSqlDatabase DatabaseMgr::getDatabase() const
{
    return database;
}

//--------------------------------------------------------------------------------------
Course DatabaseMgr::getCourse(int courseId) const
{
    Course course;

    QString queryString = QString("SELECT NAME, ICON FROM COURSE WHERE COURSE_ID=%1").arg(courseId);
    QSqlQuery query = database.exec(queryString);
    while(query.next())
    {
        QString courseName = query.value(0).toString();

        QPixmap p;
        QByteArray courseIcon = query.value(1).toByteArray();
        p.loadFromData(courseIcon);

        if(!courseIcon.isEmpty() && !courseName.contains("(old course)")) // TODO - use proxy model for this and make sure checking if byte array is empty is valid way to check that no icon was returned
            course = Course(courseId, courseName, p);
    }

    return course;
}

//--------------------------------------------------------------------------------------
QList<int> DatabaseMgr::getCourseIds() const
{
    QList<int> ids;

    QSqlQuery query = database.exec("SELECT COURSE_ID, NAME, ICON FROM COURSE");
    while(query.next())
    {
        int courseId = query.value(0).toInt();

        QString courseName = query.value(1).toString();

        QPixmap p;
        QByteArray courseIcon = query.value(2).toByteArray();
        p.loadFromData(courseIcon);

        if(!courseIcon.isEmpty() && !courseName.contains("(old course)")) // TODO - use proxy model for this and make sure checking if byte array is empty is valid way to check that no icon was returned
            ids << courseId;
    }

    return ids;
}

//--------------------------------------------------------------------------------------
Lesson DatabaseMgr::getLesson(int lessonId) const
{
    Lesson lesson;

    QString queryString = QString("SELECT NAME, NOTES, BOOKMARKED, FORCIBLY_UNCHECKED, PLAY_TIME, DURATION FROM LESSON WHERE LESSON_ID=%1").arg(lessonId);
    QSqlQuery query = database.exec(queryString);
    while(query.next())
    {
        QString lessonName = query.value(0).toString();
        if(lessonName.contains("Track") || lessonName.contains("Pista") || lessonName.contains("Lesson") || lessonName.contains("Lección"))
        {
            QRegExp regexp("(\\d+)");
            regexp.indexIn(lessonName);
            int lessonNumber = regexp.capturedTexts().first().toInt();
            lessonName = QObject::tr(QString("Lesson %1").arg(lessonNumber).toUtf8().data());
        }

        QString notes = query.value(1).toString();
        bool bookmarked = query.value(2).toBool();
        bool forciblyUnchecked = query.value(3).toBool();
        int playTime = query.value(4).toInt();
        int duration = query.value(5).toInt();
        bool completed = false;
        if((duration > 0) && ((duration - playTime) <= 1000))
            completed = true;

        lesson = Lesson(lessonId, lessonName, completed, duration, bookmarked, notes, forciblyUnchecked);
    }

    return lesson;
}

//--------------------------------------------------------------------------------------
QList<int> DatabaseMgr::getLessonIds(int courseId) const
{
    QList<int> ids;

    QString queryString = QString("SELECT LESSON_ID FROM LESSON WHERE COURSE_ID=%1").arg(courseId);
    QSqlQuery query = database.exec(queryString);
    while(query.next())
    {
        ids << query.value(0).toInt();
    }

    return ids;
}

//--------------------------------------------------------------------------------------
DatabaseMgr::DatabaseMgr()
{
    // Create/open an LT database. The simple way of doing this wasn't working on
    // Android, so I followed the solution here at
    // https://forum.qt.io/topic/36550/solved-qt-5-2-problem-deploying-sqlite-database-to-my-android-device/4:
    QFile dfile("assets:/db/language_transfer.db");
    if (dfile.exists())
    {
        dfile.copy("./language_transfer.db");
        QFile::setPermissions("./language_transfer.db",QFile::WriteOwner | QFile::ReadOwner);
    }
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./language_transfer.db");
    database.open();

    // Create a table to hold LT courses:
    database.exec("CREATE TABLE IF NOT EXISTS COURSE"
            "("
            "COURSE_ID INT PRIMARY KEY,"
            "NAME VARCHAR(150) NOT NULL,"
            "ICON BLOB"
            ")");

    // Create a table to hold LT lessons:
    database.exec("CREATE TABLE IF NOT EXISTS LESSON"
            "("
            "LESSON_ID INT PRIMARY KEY,"
            "COURSE_ID INT NOT NULL REFERENCES COURSE_ID(COURSE),"
            "NAME VARCHAR(100) NOT NULL,"
            "PLAY_TIME INT NOT NULL,"
            "DURATION INT NOT NULL,"
            "NOTES VARCHAR(1000),"
            "BOOKMARKED INT NOT NULL,"
            "FORCIBLY_UNCHECKED INT NOT NULL"
            ")");
}
