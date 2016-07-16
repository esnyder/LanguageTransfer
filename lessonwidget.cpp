#include <QFontDatabase>
#include <math.h>
#include "lessonwidget.h"
#include "ui_lessonwidget.h"

//--------------------------------------------------------------------------------------
LessonWidget::LessonWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LessonWidget),
    lessonId(-1)
{
    ui->setupUi(this);
    ui->labelButton->setFont(QFontDatabase().font("Roboto", "Regular", 18));

    // Eh, just hide the play button. It's kind of overkill, I guess:
    ui->playButton->setHidden(true);

    connect(ui->labelButton, SIGNAL(clicked()), this, SIGNAL(lessonClicked()));
    connect(ui->checkButton, SIGNAL(clicked()), this, SIGNAL(checkButtonClicked()));
    connect(ui->playButton, SIGNAL(clicked()), this, SIGNAL(lessonClicked()));
    connect(ui->notesButton, SIGNAL(clicked()), this, SIGNAL(notesButtonClicked()));
    connect(ui->favoriteButton, SIGNAL(clicked()), this, SIGNAL(favoriteButtonClicked()));
}

//--------------------------------------------------------------------------------------
LessonWidget::~LessonWidget()
{
    delete ui;
}

//--------------------------------------------------------------------------------------
int LessonWidget::getLessonId() const
{
    return lessonId;
}

//--------------------------------------------------------------------------------------
void LessonWidget::setLesson(int id)
{
    lessonId = id;

    Lesson lesson = DatabaseMgr::Instance()->getLesson(id);
    int minutes = lesson.duration / 60000;
    int seconds = floor(fmod(lesson.duration, 60000) / 1000);
    QString timeText = QString("%1:%2").arg(minutes, 1, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    ui->labelButton->setText(
                QString("%1<br><font color='silver'>%2</font>").arg(lesson.name).arg(timeText));

    // The lesson has not been completed:
    if(!lesson.completed)
    {
        ui->checkButton->setVisible(false);
    }
    // Otherwise, the lesson is complete and the user wants to see the checkmark:
    else
    {
        ui->checkButton->setVisible(true);
        ui->checkButton->setIcon(":/images/check-circle.svg", QSize(30, 30));
    }

    if(lesson.notes.isEmpty())
        ui->notesButton->setIcon(":/images/sticky-note-o.svg", QSize(24, 30));
    else
        ui->notesButton->setIcon(":/images/sticky-note.svg", QSize(24, 30));

    if(lesson.bookmarked)
        ui->favoriteButton->setIcon(":/images/bookmark-filled.svg", QSize(30, 30));
    else
        ui->favoriteButton->setIcon(":/images/bookmark.svg", QSize(30, 30));
}
