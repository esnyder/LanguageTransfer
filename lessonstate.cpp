#include <QSqlQuery>
#include "ui_application.h"
#include "coursestate.h"
#include "playerstate.h"
#include "notesstate.h"
#include "lessonstate.h"

//--------------------------------------------------------------------------------------
LessonState::LessonState(
    int courseId,
    Application* parent) :
    ApplicationState(parent),
    currentCourseId(courseId)
{
}

//--------------------------------------------------------------------------------------
LessonState::~LessonState()
{
}

//--------------------------------------------------------------------------------------
void LessonState::onEntry(Application* owner)
{
    owner->getUserInterface()->stackedWidget->setCurrentIndex(Application::InteractionPage);
    owner->getUserInterface()->stackedWidget2->setCurrentIndex(Application::LessonPage);
    owner->getUserInterface()->backButton->show();
    owner->getUserInterface()->banner->setText(
                DatabaseMgr::Instance()->getCourse(currentCourseId).name.split("(").first());

    // Show the user the lesson list:
    owner->setLessons(DatabaseMgr::Instance()->getLessonIds(currentCourseId));
}

//--------------------------------------------------------------------------------------
void LessonState::lessonClicked(const QModelIndex& index)
{
    owner->transition(
                new PlayerState(
                    currentCourseId,
                    owner->getLesson(index).id,
                    owner));
}

//--------------------------------------------------------------------------------------
void LessonState::notesButtonClicked(const QModelIndex& index)
{
    owner->transition(
                new NotesState(
                    currentCourseId,
                    owner->getLesson(index).id,
                    owner));
}

//--------------------------------------------------------------------------------------
void LessonState::backButtonClicked()
{
    owner->transition(new CourseState(owner));
}
