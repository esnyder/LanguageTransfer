#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "applicationstate.h"

class SplashState : public ApplicationState
{

    Q_OBJECT

public:
    SplashState(Application* parent = 0);

    virtual ~SplashState();

    virtual void onEntry(Application* o);

public slots:
    virtual void playListRequestFinished(QNetworkReply* reply);

    virtual void initializationTimerFinished();

private:
    bool timerFinished;

    bool receivedReply;


};

#endif // SPLASHSTATE_H
