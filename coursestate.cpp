#include <QSqlQuery>
#include "ui_application.h"
#include "lessonstate.h"
#include "coursestate.h"

//--------------------------------------------------------------------------------------
CourseState::CourseState(Application* parent) : ApplicationState(parent)
{

}

//--------------------------------------------------------------------------------------
CourseState::~CourseState()
{

}

//--------------------------------------------------------------------------------------
void CourseState::onEntry(Application* owner)
{
    owner->getUserInterface()->stackedWidget->setCurrentIndex(Application::InteractionPage);
    owner->getUserInterface()->stackedWidget2->setCurrentIndex(Application::CoursePage);
    owner->getUserInterface()->backButton->hide();
    owner->getUserInterface()->banner->setText("  Language Transfer");

    // Now that the course table is up-to-date, show the user the course list:
    owner->setCourses(DatabaseMgr::Instance()->getCourseIds());
}

//--------------------------------------------------------------------------------------
void CourseState::backButtonClicked()
{
    qApp->quit();
}

//--------------------------------------------------------------------------------------
void CourseState::courseClicked(const QModelIndex& index)
{
    owner->transition(
                new LessonState(
                    owner->getCourse(index).id,
                    owner));
}
