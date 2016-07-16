#ifndef STATEMACHINE_H
#define STATEMACHINE_H


#include "state.h"


template <class TYPE>
class StateMachine
{

public:
    StateMachine(TYPE* o) :
        owner(o),
        currentState(0),
        previousState(0) {}

    inline TYPE* getOwner() const { return owner; }

    inline State<TYPE>* getCurrentState() const { return currentState; }

    inline State<TYPE>* getPreviousState() const { return previousState; }

    void transition(State<TYPE>* newState)
    {
        previousState = currentState;
        if(previousState)
            previousState->onExit(owner);

        currentState = newState;
        if(currentState)
            currentState->onEntry(owner);
    }

    void revert()
    {
        transition(previousState);
    }

private:
    TYPE* owner;

    State<TYPE>* currentState;

    State<TYPE>* previousState;

};

#endif // STATEMACHINE_H
