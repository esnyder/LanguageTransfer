#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{

    Q_OBJECT

public:
    explicit ClickableLabel(
        QWidget* parent = 0,
        Qt::WindowFlags f = 0);

    explicit ClickableLabel(
        const QString& text,
        QWidget* parent = 0,
        Qt::WindowFlags f = 0);

    virtual ~ClickableLabel();

signals:
    void clicked();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H
