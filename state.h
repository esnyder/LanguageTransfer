#ifndef STATE_H
#define STATE_H

#include <QObject>

template <class TYPE>
class State
{

public:
    explicit State() {}

    virtual ~State() {}

    virtual void onEntry(TYPE* owner) { Q_UNUSED(owner); }

    virtual void execute(TYPE* owner) { Q_UNUSED(owner); }

    virtual void onExit(TYPE* owner) { Q_UNUSED(owner); }

};

#endif // STATE_H
