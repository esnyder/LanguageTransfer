#include <QSqlQuery>
#include <math.h>
#include "ui_application.h"
#include "lessonstate.h"
#include "playerstate.h"


//--------------------------------------------------------------------------------------
PlayerState::PlayerState(
    int courseId,
    int lessonId,
    Application* parent) :
    ApplicationState(parent),
    currentCourseId(courseId),
    currentLessonId(lessonId),
    isPlaying(false)
{

}


//--------------------------------------------------------------------------------------
PlayerState::~PlayerState()
{

}


//--------------------------------------------------------------------------------------
void PlayerState::onEntry(Application* owner)
{
    Lesson lesson = DatabaseMgr::Instance()->getLesson(currentLessonId);
    owner->getUserInterface()->stackedWidget->setCurrentIndex(Application::InteractionPage);
    owner->getUserInterface()->stackedWidget2->setCurrentIndex(Application::PlayerPage);
    owner->getUserInterface()->backButton->show();
    owner->getUserInterface()->banner->setText(lesson.name);
    owner->getUserInterface()->seekSlider->setValue(0);
    owner->getUserInterface()->seekSlider->setRange(0, (int)lesson.duration);
    owner->getGearsMovie()->setPaused(true);
    owner->getAudioPlayer()->setAudioRole(QAudio::MusicRole);

    QString streamPath = QString("https://api.soundcloud.com/tracks/%1/stream").arg(currentLessonId);
    Application::AppendClientId(streamPath);
    owner->getAudioPlayer()->setMedia(QUrl(streamPath));

    updateTimeIndicators();
}


//--------------------------------------------------------------------------------------
void PlayerState::onExit(Application* owner)
{
    Q_UNUSED(owner)

    if(isPlaying)
        playButtonClicked();
}


//--------------------------------------------------------------------------------------
void PlayerState::backButtonClicked()
{
    owner->transition(
                new LessonState(
                    currentCourseId,
                    owner));
}


//--------------------------------------------------------------------------------------
void PlayerState::playButtonClicked()
{
    isPlaying = !isPlaying;

    if(isPlaying)
    {
        owner->getAudioPlayer()->play();
        owner->getGearsMovie()->setPaused(false);
    }
    else
    {
        owner->getAudioPlayer()->pause();
        owner->getGearsMovie()->setPaused(true);
    }
}


//--------------------------------------------------------------------------------------
void PlayerState::sliderMoved(int value)
{
    owner->getGearsMovie()->setPaused(true);
    owner->getAudioPlayer()->stop();

    disconnect(owner->getAudioPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(trackPositionChanged(qint64)));
    owner->getAudioPlayer()->setPosition(value);

    updateTimeIndicators();
}


//--------------------------------------------------------------------------------------
void PlayerState::sliderReleased()
{
    connect(owner->getAudioPlayer(), SIGNAL(positionChanged(qint64)), this, SLOT(trackPositionChanged(qint64)));

    if(isPlaying)
    {
        owner->getGearsMovie()->setPaused(false);
        owner->getAudioPlayer()->play();
    }
}


//--------------------------------------------------------------------------------------
void PlayerState::trackDurationChanged(qint64 duration)
{
    owner->getUserInterface()->seekSlider->setRange(0, (int)duration);
    updateTimeIndicators();
}


//--------------------------------------------------------------------------------------
void PlayerState::trackPositionChanged(qint64 position)
{
    owner->getUserInterface()->seekSlider->setValue((int)position);

    DatabaseMgr::Instance()->getDatabase().exec(QString("UPDATE LESSON "
                    "SET PLAY_TIME=%1 "
                    "WHERE LESSON_ID=%2 AND PLAY_TIME<%1")
                    .arg(position).arg(currentLessonId));

    updateTimeIndicators();

    if(owner->getAudioPlayer()->position() == owner->getAudioPlayer()->duration())
    {
        owner->getGearsMovie()->setPaused(true);
        owner->getAudioPlayer()->pause();
    }
}


//--------------------------------------------------------------------------------------
void PlayerState::updateTimeIndicators()
{
    int startTime = owner->getUserInterface()->seekSlider->value();
    int minutes = startTime / 60000;
    int seconds = floor(fmod(startTime, 60000) / 1000);
    owner->getUserInterface()->startTime->setText(QString("%1:%2").arg(minutes, 1, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));

    Lesson lesson = DatabaseMgr::Instance()->getLesson(currentLessonId);
    int endTime = lesson.duration;
    minutes = endTime / 60000;
    seconds = floor(fmod(endTime, 60000) / 1000);
    owner->getUserInterface()->endTime->setText(QString("%1:%2").arg(minutes, 1, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
}
