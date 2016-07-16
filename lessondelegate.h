#ifndef LESSONDELEGATE_H
#define LESSONDELEGATE_H

#include <QStyledItemDelegate>
#include "lessonlistmodel.h"

class LessonDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:
    explicit LessonDelegate(
        LessonListModel* model = 0);

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
    void lessonClicked(
        const QModelIndex& index);

    void notesButtonClicked(
        const QModelIndex& index);

private:
    void onLessonClicked();

    void onCheckButtonClicked();

    void onNotesButtonClicked();

    void onFavoriteButtonClicked();

private:
    LessonListModel* model;

};

#endif // LESSONDELEGATE_H
