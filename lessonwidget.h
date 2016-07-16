#ifndef LESSONWIDGET_H
#define LESSONWIDGET_H

#include <QWidget>
#include "databasemgr.h"

namespace Ui
{
    class LessonWidget;
}

class LessonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LessonWidget(QWidget* parent = 0);

    virtual ~LessonWidget();

    int getLessonId() const;

    void setLesson(int lessonId);

signals:
    void lessonClicked();

    void checkButtonClicked();

    void notesButtonClicked();

    void favoriteButtonClicked();

private:
    Ui::LessonWidget* ui;

    int lessonId;

};

#endif // LESSONWIDGET_H
