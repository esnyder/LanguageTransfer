#include <QSqlQuery>
#include "ui_application.h"
#include "lessonstate.h"
#include "notesstate.h"


//--------------------------------------------------------------------------------------
NotesState::NotesState(
    int courseId,
    int lessonId,
    Application* parent) :
    ApplicationState(parent),
    currentCourseId(courseId),
    currentLessonId(lessonId)
{
    timer.setSingleShot(true);
    timer.setInterval(400);
    connect(&timer, &QTimer::timeout, this, &NotesState::onSaveTimerFinished);
}


//--------------------------------------------------------------------------------------
NotesState::~NotesState()
{
    timer.stop();
}


//--------------------------------------------------------------------------------------
void NotesState::onEntry(Application* owner)
{
    Lesson lesson = DatabaseMgr::Instance()->getLesson(currentLessonId);
    owner->getUserInterface()->stackedWidget->setCurrentIndex(Application::InteractionPage);
    owner->getUserInterface()->stackedWidget2->setCurrentIndex(Application::NotesPage);
    owner->getUserInterface()->backButton->show();
    owner->getUserInterface()->banner->setText(lesson.name);
    owner->getUserInterface()->notesTextEdit->setText(lesson.notes);
    owner->getUserInterface()->notesSaveStatusLabel->setText("Notes saved.");

    // Move the cursor to the end of the notes:
    QTextCursor tmpCursor = owner->getUserInterface()->notesTextEdit->textCursor();
    tmpCursor.movePosition(QTextCursor::End);
    owner->getUserInterface()->notesTextEdit->setTextCursor(tmpCursor);
}

//--------------------------------------------------------------------------------------
void NotesState::notesChanged()
{
    QString notes = owner->getUserInterface()->notesTextEdit->toPlainText();
    DatabaseMgr::Instance()->getDatabase().exec(QString("UPDATE LESSON "
                    "SET NOTES='%1' "
                    "WHERE LESSON_ID=%2")
                    .arg(notes).arg(currentLessonId));

    owner->getUserInterface()->notesSaveStatusLabel->setText("Saving notes...");
    timer.start();
}

//--------------------------------------------------------------------------------------
void NotesState::backButtonClicked()
{
    owner->transition(
                new LessonState(
                    currentCourseId,
                    owner));
}

//--------------------------------------------------------------------------------------
void NotesState::onSaveTimerFinished()
{
    owner->getUserInterface()->notesSaveStatusLabel->setText("Notes saved.");
}
