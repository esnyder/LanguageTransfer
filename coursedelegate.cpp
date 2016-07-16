#include "coursewidget.h"
#include "coursedelegate.h"

//--------------------------------------------------------------------------------------
const int CourseDelegate::DefaultHeight = 70;

//--------------------------------------------------------------------------------------
CourseDelegate::CourseDelegate(
    CourseListModel* model):
    QStyledItemDelegate(model),
    model(model)
{
}

//--------------------------------------------------------------------------------------
QWidget* CourseDelegate::createEditor(
    QWidget* parent,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    CourseWidget* editor = new CourseWidget(parent);
    connect(editor, &CourseWidget::courseClicked, this, &CourseDelegate::onCourseClicked);
    return editor;
}

//--------------------------------------------------------------------------------------
void CourseDelegate::setEditorData(
    QWidget* editor,
    const QModelIndex& index) const
{
    CourseWidget* widget = qobject_cast<CourseWidget*>(editor);
    if(widget)
    {
        widget->setCourse(model->getCourseId(index));
    }
}

//--------------------------------------------------------------------------------------
QSize CourseDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    QSize hint = QStyledItemDelegate::sizeHint(option, index);
    hint.setHeight(DefaultHeight);
    return hint;
}

//--------------------------------------------------------------------------------------
void CourseDelegate::updateEditorGeometry(
    QWidget* editor,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

//--------------------------------------------------------------------------------------
void CourseDelegate::onCourseClicked()
{
    CourseWidget* editor = qobject_cast<CourseWidget*>(sender());
    if(editor)
    {
        emit courseClicked(model->getIndex(editor->getCourseId()));
    }
}
