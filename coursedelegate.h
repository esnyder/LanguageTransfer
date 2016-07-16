#ifndef COURSEDELEGATE_H
#define COURSEDELEGATE_H

#include <QStyledItemDelegate>
#include "courselistmodel.h"

class CourseDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:
    explicit CourseDelegate(
        CourseListModel* model = 0);

    virtual QWidget* createEditor(
        QWidget* parent,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    virtual void setEditorData(
        QWidget* editor,
        const QModelIndex& index) const;

    virtual QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    virtual void updateEditorGeometry(
        QWidget* editor,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

public:
    static const int DefaultHeight;

signals:
    void courseClicked(
        const QModelIndex& index);

private:
    void onCourseClicked();

private:
    CourseListModel* model;

};

#endif // COURSEDELEGATE_H
