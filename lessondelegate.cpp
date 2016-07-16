#include "lessonwidget.h"
#include "lessondelegate.h"

//--------------------------------------------------------------------------------------
const int LessonDelegate::DefaultHeight = 70;

//--------------------------------------------------------------------------------------
LessonDelegate::LessonDelegate(
    LessonListModel* model):
    QStyledItemDelegate(model),
    model(model)
{
}

//--------------------------------------------------------------------------------------
QWidget* LessonDelegate::createEditor(
    QWidget* parent,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    LessonWidget* editor = new LessonWidget(parent);
    connect(editor, &LessonWidget::lessonClicked, this, &LessonDelegate::onLessonClicked);
    connect(editor, &LessonWidget::checkButtonClicked, this, &LessonDelegate::onCheckButtonClicked);
    connect(editor, &LessonWidget::notesButtonClicked, this, &LessonDelegate::onNotesButtonClicked);
    connect(editor, &LessonWidget::favoriteButtonClicked, this, &LessonDelegate::onFavoriteButtonClicked);
    return editor;
}

//--------------------------------------------------------------------------------------
void LessonDelegate::setEditorData(
    QWidget* editor,
    const QModelIndex& index) const
{
    LessonWidget* widget = qobject_cast<LessonWidget*>(editor);
    if(widget)
    {
        widget->setLesson(model->getLessonId(index));
    }
}

//--------------------------------------------------------------------------------------
QSize LessonDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    QSize hint = QStyledItemDelegate::sizeHint(option, index);
    hint.setHeight(DefaultHeight);
    return hint;
}

//--------------------------------------------------------------------------------------
void LessonDelegate::updateEditorGeometry(
    QWidget* editor,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

//--------------------------------------------------------------------------------------
void LessonDelegate::onLessonClicked()
{
    LessonWidget* editor = qobject_cast<LessonWidget*>(sender());
    if(editor)
    {
        emit lessonClicked(model->getIndex(editor->getLessonId()));
    }
}

//--------------------------------------------------------------------------------------
void LessonDelegate::onCheckButtonClicked()
{
    LessonWidget* editor = qobject_cast<LessonWidget*>(sender());
    if(editor)
    {
        QModelIndex index = model->getIndex(editor->getLessonId());
        model->toggleCheckmark(index);
    }
}

//--------------------------------------------------------------------------------------
void LessonDelegate::onNotesButtonClicked()
{
    LessonWidget* editor = qobject_cast<LessonWidget*>(sender());
    if(editor)
    {
        emit notesButtonClicked(model->getIndex(editor->getLessonId()));
    }
}

//--------------------------------------------------------------------------------------
void LessonDelegate::onFavoriteButtonClicked()
{
    LessonWidget* editor = qobject_cast<LessonWidget*>(sender());
    if(editor)
    {
        QModelIndex index = model->getIndex(editor->getLessonId());
        model->toggleBookmark(index);
    }
}
