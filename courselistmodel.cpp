#include "courselistmodel.h"

//--------------------------------------------------------------------------------------
CourseListModel::CourseListModel(
    const QList<int>& ids,
    QObject* parent) :
    QAbstractListModel(parent),
    courseIds(ids)
{
}

//--------------------------------------------------------------------------------------
CourseListModel::~CourseListModel()
{
}

//--------------------------------------------------------------------------------------
int CourseListModel::rowCount(
    const QModelIndex& index) const
{
    Q_UNUSED(index)
    return courseIds.size();
}

//--------------------------------------------------------------------------------------
QVariant CourseListModel::data(
    const QModelIndex& index,
    int role) const
{
    QVariant data;

    /*
    Course course = DatabaseMgr::Instance()->getCourse(getCourseId(index));

    switch(role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        data = course.name;
        break;
    case Qt::DecorationRole:
        data = course.icon;
        break;
    }
    */

    return data;
}

//--------------------------------------------------------------------------------------
bool CourseListModel::setData(
    const QModelIndex& index,
    const QVariant& value,
    int role)
{
    return false;
}

//--------------------------------------------------------------------------------------
int CourseListModel::getCourseId(
    const QModelIndex& index) const
{
    return courseIds.at(index.row());
}

//--------------------------------------------------------------------------------------
QModelIndex CourseListModel::getIndex(
    int id) const
{
    int index = courseIds.indexOf(id);
    return createIndex(
                index,
                0);
}

//--------------------------------------------------------------------------------------
void CourseListModel::setCourses(
    const QList<int>& ids)
{
    beginResetModel();
    courseIds = ids;
    endResetModel();
}
