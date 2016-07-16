#include <QFontDatabase>
#include "databasemgr.h"
#include "coursewidget.h"
#include "ui_coursewidget.h"

//--------------------------------------------------------------------------------------
CourseWidget::CourseWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CourseWidget),
    courseId(-1)
{
    ui->setupUi(this);
    ui->iconButton->hide(); // hide for now b/c the SoundCloud images aren't clear
    ui->labelButton->setFont(QFontDatabase().font("Roboto", "Regular", 18));
    connect(ui->iconButton, SIGNAL(clicked()), this, SIGNAL(courseClicked()));
    connect(ui->labelButton, SIGNAL(clicked()), this, SIGNAL(courseClicked()));
}

//--------------------------------------------------------------------------------------
CourseWidget::~CourseWidget()
{
    delete ui;
}

//--------------------------------------------------------------------------------------
int CourseWidget::getCourseId() const
{
    return courseId;
}

//--------------------------------------------------------------------------------------
void CourseWidget::setCourse(int id)
{
    courseId = id;

    Course course = DatabaseMgr::Instance()->getCourse(id);
    ui->iconButton->setPixmap(
                course.icon.scaled(ui->iconButton->width(), ui->iconButton->height()));

    QString labelText;
    try
    {
        QStringList courseTextList = course.name.split("(");
        QString courseTitle = courseTextList.at(0);
        QString courseInfo;
        if(courseTextList.size() > 1)
        {
            courseInfo = courseTextList.at(1);
            courseInfo.remove(")");

            if(courseInfo.size())
                courseInfo[0] = courseInfo[0].toUpper();

            courseInfo = "<br>" + courseInfo;
        }
        labelText = courseTitle + QString("<font color='silver'>%1</font>").arg(courseInfo);
    }
    catch (...)
    {
        labelText = course.name;
    }
    ui->labelButton->setText(labelText);
}
