#ifndef COURSESTATE_H
#define COURSESTATE_H

#include "applicationstate.h"

class CourseState : public ApplicationState
{

    Q_OBJECT

public:
    CourseState(Application* parent = 0);

    virtual ~CourseState();

    virtual void onEntry(Application* owner);

public slots:
    virtual void backButtonClicked();

    virtual void courseClicked(const QModelIndex& index);

};

#endif // COURSESTATE_H
