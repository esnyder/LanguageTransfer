#include <QSqlQuery>
#include "lessonlistmodel.h"

//--------------------------------------------------------------------------------------
LessonListModel::LessonListModel(
    const QList<int>& ids,
    QObject* parent) :
    QAbstractListModel(parent),
    lessonIds(ids)
{
}

//--------------------------------------------------------------------------------------
LessonListModel::~LessonListModel()
{
}

//--------------------------------------------------------------------------------------
int LessonListModel::rowCount(
    const QModelIndex& index) const
{
    Q_UNUSED(index)
    return lessonIds.size();
}

//--------------------------------------------------------------------------------------
QVariant LessonListModel::data(
    const QModelIndex& index,
    int role) const
{
    QVariant data;

    /*
    Lesson lesson = DatabaseMgr::Instance()->getLesson(getLessonId(index));

    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        data = lesson.name;
        break;
    case CheckedRole:
        data = lesson.completed;
        break;
    case NotesRole:
        data = lesson.notes;
        break;
    case BookmarkedRole:
        data = lesson.bookmarked;
        break;
    }
    */

    return data;
}

//--------------------------------------------------------------------------------------
bool LessonListModel::setData(
    const QModelIndex& index,
    const QVariant& value,
    int role)
{
    return false;
}

//--------------------------------------------------------------------------------------
int LessonListModel::getLessonId(
    const QModelIndex& index) const
{
    return lessonIds.at(index.row());
}

//--------------------------------------------------------------------------------------
void LessonListModel::setLessons(
    const QList<int>& ids)
{
    beginResetModel();
    lessonIds = ids;
    endResetModel();
}

//--------------------------------------------------------------------------------------
QModelIndex LessonListModel::getIndex(
    int id) const
{
    int index = lessonIds.indexOf(id);
    return createIndex(
                index,
                0);
}

//--------------------------------------------------------------------------------------
void LessonListModel::toggleCheckmark(
    const QModelIndex& index)
{
    int lessonId = getLessonId(index);
    DatabaseMgr::Instance()->getDatabase().exec(QString("UPDATE LESSON "
                    "SET PLAY_TIME=0 "
                    "WHERE LESSON_ID=%1")
                    .arg(lessonId));

    dataChanged(index, index);
}

//--------------------------------------------------------------------------------------
void LessonListModel::toggleBookmark(
    const QModelIndex& index)
{
    int lessonId = getLessonId(index);
    bool bookmarked = DatabaseMgr::Instance()->getLesson(lessonId).bookmarked;
    DatabaseMgr::Instance()->getDatabase().exec(QString("UPDATE LESSON "
                    "SET BOOKMARKED=%1 "
                    "WHERE LESSON_ID=%2")
                    .arg(!bookmarked).arg(lessonId));

    dataChanged(index, index);
}
