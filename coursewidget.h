#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H

#include <QWidget>

namespace Ui
{
    class CourseWidget;
}

class CourseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CourseWidget(QWidget* parent = 0);

    virtual ~CourseWidget();

    int getCourseId() const;

    void setCourse(int CourseId);

signals:
    void courseClicked();

private:
    Ui::CourseWidget* ui;

    int courseId;

};

#endif // COURSEWIDGET_H
