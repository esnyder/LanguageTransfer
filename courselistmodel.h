#ifndef COURSELISTMODEL_H
#define COURSELISTMODEL_H

#include <QAbstractListModel>
#include "databasemgr.h"

class CourseListModel : public QAbstractListModel
{

    Q_OBJECT

public:
    CourseListModel(
        const QList<int>& ids = QList<int>(),
        QObject* parent = 0);

    virtual ~CourseListModel();

    virtual int rowCount(
        const QModelIndex& index) const;

    virtual QVariant data(
        const QModelIndex& index,
        int role) const;

    virtual bool setData(
        const QModelIndex& index,
        const QVariant& value,
        int role);

    int getCourseId(
        const QModelIndex& index) const;

    QModelIndex getIndex(
        int id) const;

    void setCourses(
        const QList<int>& ids);

private:
    QList<int> courseIds;

};

#endif // COURSELISTMODEL_H
