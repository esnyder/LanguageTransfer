#ifndef LESSONSTATE_H
#define LESSONSTATE_H

#include "applicationstate.h"

class LessonState : public ApplicationState
{

    Q_OBJECT

public:
    LessonState(
        int courseId,
        Application* parent = 0);

    virtual ~LessonState();

    virtual void onEntry(Application* owner);

public slots:
    virtual void lessonClicked(const QModelIndex& index);

    virtual void notesButtonClicked(const QModelIndex& index);

    virtual void backButtonClicked();

private:
    int currentCourseId;

};

#endif // LESSONSTATE_H
