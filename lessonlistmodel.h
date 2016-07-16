#ifndef LESSONLISTMODEL_H
#define LESSONLISTMODEL_H

#include <QAbstractListModel>
#include "databasemgr.h"

class LessonListModel : public QAbstractListModel
{

    Q_OBJECT

public:
    enum LessonRole
    {
        CheckedRole = Qt::UserRole,
        NotesRole,
        BookmarkedRole
    };

    LessonListModel(
        const QList<int>& ids = QList<int>(),
        QObject* parent = 0);

    virtual ~LessonListModel();

    virtual int rowCount(
        const QModelIndex& index) const;

    virtual QVariant data(
        const QModelIndex& index,
        int role) const;

    virtual bool setData(
        const QModelIndex& index,
        const QVariant& value,
        int role);

    int getLessonId(
        const QModelIndex& index) const;

    void setLessons(
        const QList<int>& ids);

    QModelIndex getIndex(
        int id) const;

    void toggleCheckmark(
        const QModelIndex& index);

    void toggleBookmark(
        const QModelIndex& index);

private:
    QList<int> lessonIds;

};

#endif // LESSONLISTMODEL_H
