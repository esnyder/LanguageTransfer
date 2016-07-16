#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "applicationstate.h"

class PlayerState : public ApplicationState
{

    Q_OBJECT

public:
    PlayerState(
        int courseId,
        int lessonId,
        Application* parent = 0);

    virtual ~PlayerState();

    virtual void onEntry(Application* owner);

    virtual void onExit(Application* owner);

public slots:
    virtual void backButtonClicked();

    virtual void playButtonClicked();

    virtual void sliderMoved(int);

    virtual void sliderReleased();

    virtual void trackDurationChanged(qint64 duration);

    virtual void trackPositionChanged(qint64 position);

private:
    //! Update the time indicators using the given start time, in
    //! milliseconds. If  start time is negative, it is are determined
    //! from the current position of the app's audio player. The end time
    //! will be set to the lesson's duration.
    void updateTimeIndicators();

private:
    int currentCourseId;

    int currentLessonId;

    bool isPlaying;

};

#endif // PLAYERSTATE_H
