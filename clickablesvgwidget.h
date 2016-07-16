#ifndef CLICKABLESVGWIDGET_H
#define CLICKABLESVGWIDGET_H

#include <QLabel>
#include <QSvgWidget>
#include <QBoxLayout>
#include <QMouseEvent>

class ClickableSvgWidget : public QLabel
{

    Q_OBJECT

public:
    explicit ClickableSvgWidget(
        QWidget* parent = 0);

    explicit ClickableSvgWidget(
        const QString& file,
        const QSize& iconSize,
        QWidget* parent = 0);

    virtual ~ClickableSvgWidget();

    void setIcon(
        const QString& file,
        const QSize& iconSize);

signals:
    void clicked();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    QBoxLayout* layout;

    QSvgWidget* svgWidget;

};

#endif // CLICKABLESVGWIDGET_H
