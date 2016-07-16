#ifndef DATABASEMGR_H
#define DATABASEMGR_H

#include <QList>
#include <QIcon>
#include <QSqlDatabase>

struct Course
{
    int id;

    QString name;

    QPixmap icon;

    Course(int id = -1, const QString& name = "", const QPixmap& icon = QPixmap())
        : id(id), name(name), icon(icon) {}
};
typedef QList<Course> CourseList;

struct Lesson
{
    int id;

    QString name;

    bool completed;

    int duration; // in milliseconds

    bool bookmarked;

    QString notes;

    bool forciblyUnchecked;

    inline bool operator ==(const Lesson& other)
    {
        return (id == other.id)
                && (name == other.name)
                && (completed == other.completed)
                && (duration == other.duration)
                && (bookmarked == other.bookmarked)
                && (notes == other.notes)
                && (forciblyUnchecked == other.forciblyUnchecked);
    }

    Lesson(int id = -1, const QString& name = "", bool completed = false, int duration = -1, bool bookmarked = false, QString notes = "", bool forciblyUnchecked = false)
        : id(id), name(name), completed(completed), duration(duration), bookmarked(bookmarked), notes(notes), forciblyUnchecked(forciblyUnchecked) {}
};
typedef QList<Lesson> LessonList;

class DatabaseMgr
{

public:
    static DatabaseMgr* Instance();

    QSqlDatabase getDatabase() const;

    Course getCourse(
        int courseId) const;

    QList<int> getCourseIds() const;

    Lesson getLesson(
        int lessonId) const;

    QList<int> getLessonIds(
        int courseId) const;

private:
    DatabaseMgr();

    static DatabaseMgr* instance;

    QSqlDatabase database;

};

#endif // DATABASEMGR_H
