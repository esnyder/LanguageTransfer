#include <QTimer>
#include "ui_application.h"
#include "coursestate.h"
#include "splashstate.h"

//--------------------------------------------------------------------------------------
SplashState::SplashState(Application* parent) :
    ApplicationState(parent),
    timerFinished(false),
    receivedReply(false)
{

}

//--------------------------------------------------------------------------------------
SplashState::~SplashState()
{

}

//--------------------------------------------------------------------------------------
void SplashState::onEntry(Application* o)
{
    owner = o;
    owner->getUserInterface()->stackedWidget->setCurrentIndex(Application::SplashScreenPage);

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(initializationTimerFinished()));
    timer->start();

    owner->initializeDatabase();
}

//--------------------------------------------------------------------------------------
void SplashState::playListRequestFinished(QNetworkReply* reply)
{
    owner->populateDatabase(reply);

    receivedReply = true;

    if(timerFinished)
        owner->transition(new CourseState(owner));
}

//--------------------------------------------------------------------------------------
void SplashState::initializationTimerFinished()
{
    timerFinished = true;

    if(receivedReply)
        owner->transition(new CourseState(owner));
}
