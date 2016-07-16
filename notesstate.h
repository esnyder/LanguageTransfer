#ifndef NOTESSTATE_H
#define NOTESSTATE_H

#include <QTimer>
#include "applicationstate.h"

class NotesState : public ApplicationState
{

    Q_OBJECT

public:
    NotesState(
        int courseId,
        int lessonId,
        Application* parent = 0);

    virtual ~NotesState();

    virtual void onEntry(Application* owner);

public slots:
    virtual void notesChanged();

    virtual void backButtonClicked();

private:
    void onSaveTimerFinished();

private:
    int currentCourseId;

    int currentLessonId;

    QTimer timer;

};

#endif // NOTESSTATE_H
