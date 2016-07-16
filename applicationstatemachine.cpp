#include "applicationstatemachine.h"

//--------------------------------------------------------------------------------------
ApplicationStateMachine::ApplicationStateMachine(
    Application* o) :
    ApplicationHandler(o),
    StateMachine<Application>(o)
{

}

//--------------------------------------------------------------------------------------
ApplicationState* ApplicationStateMachine::getCurrentState() const
{
    return dynamic_cast<ApplicationState*>(StateMachine::getCurrentState());
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::playListRequestFinished(QNetworkReply* reply)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->playListRequestFinished(reply);
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::backButtonClicked()
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->backButtonClicked();
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::courseClicked(const QModelIndex& index)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->courseClicked(index);
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::lessonClicked(const QModelIndex& index)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->lessonClicked(index);
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::notesButtonClicked(const QModelIndex& index)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->notesButtonClicked(index);
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::notesChanged()
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->notesChanged();
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::playButtonClicked()
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->playButtonClicked();
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::sliderMoved(int position)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->sliderMoved(position);
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::sliderReleased()
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->sliderReleased();
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::trackDurationChanged(qint64 duration)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->trackDurationChanged(duration);
    }
}

//--------------------------------------------------------------------------------------
void ApplicationStateMachine::trackPositionChanged(qint64 position)
{
    ApplicationState* current = getCurrentState();
    if(current)
    {
        current->trackPositionChanged(position);
    }
}
