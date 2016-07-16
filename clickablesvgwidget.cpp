#include "clickablesvgwidget.h"

//--------------------------------------------------------------------------------------
ClickableSvgWidget::ClickableSvgWidget(
    QWidget* parent) :
    QLabel(parent),
    layout(new QBoxLayout(QBoxLayout::LeftToRight, this)),
    svgWidget(new QSvgWidget(this))
{
    layout->addWidget(svgWidget);
}

//--------------------------------------------------------------------------------------
ClickableSvgWidget::ClickableSvgWidget(
    const QString& file,
    const QSize& iconSize,
    QWidget* parent) :
    QLabel(parent),
    layout(new QBoxLayout(QBoxLayout::LeftToRight, this)),
    svgWidget(new QSvgWidget(this))
{
   layout->addWidget(svgWidget);
   setIcon(file, iconSize);
}

//--------------------------------------------------------------------------------------
ClickableSvgWidget::~ClickableSvgWidget()
{

}

//--------------------------------------------------------------------------------------
void ClickableSvgWidget::setIcon(
    const QString& file,
    const QSize& iconSize)
{
    svgWidget->load(file);
    svgWidget->setFixedSize(iconSize);
}

//--------------------------------------------------------------------------------------
void ClickableSvgWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QPointF localPosition = event->localPos();
    if(rect().contains(localPosition.x(), localPosition.y()))
    {
        emit clicked();
    }
}
