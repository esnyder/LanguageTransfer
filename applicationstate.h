#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include "state.h"
#include "applicationhandler.h"
#include "application.h"

class Application;

class ApplicationState : public ApplicationHandler, public State<Application>
{

    Q_OBJECT

public:
    ApplicationState(Application* parent = 0);

protected:
    Application* owner;

};

#endif // APPLICATIONSTATE_H
