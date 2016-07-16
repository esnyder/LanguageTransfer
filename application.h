#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QListWidgetItem>
#include <QAction>
#include <QMovie>
#include <QMediaPlayer>
#include "databasemgr.h"
#include "applicationstatemachine.h"
#include "applicationstate.h"
#include "courselistmodel.h"
#include "lessonlistmodel.h"

class ApplicationStateMachine;
class ApplicationState;

namespace Ui {
class Application;
}

class Application : public QMainWindow
{

    Q_OBJECT

public:
    enum MajorPage
    {
        SplashScreenPage = 0,
        InteractionPage
    };

    enum MinorPage
    {
        CoursePage = 0,
        LessonPage,
        PlayerPage,
        NotesPage
    };

    explicit Application(QWidget* parent = 0);

    ~Application();

    Ui::Application* getUserInterface() const;

    QMovie* getGearsMovie() const;

    QMediaPlayer* getAudioPlayer() const;

    const QList<Course>& getCourses() const;

    Course getCourse(const QModelIndex& index) const;

    Lesson getLesson(const QModelIndex& index) const;

    void transition(ApplicationState* state);

    void initializeDatabase();

    void populateDatabase(QNetworkReply* reply);

    static void AppendClientId(QString& url);

public slots:
    void openMenu();

    void setCourses(const QList<int>& ids);

    void setLessons(const QList<int>& ids);

signals:
    void backButtonReleased();

protected:
    virtual void keyReleaseEvent(QKeyEvent* event);

private:
    QByteArray loadImage(const QString& urlPath);

private:
    Ui::Application* ui;

    ApplicationStateMachine* stateMachine;

    QAction* homeOption;

    QAction* patronOption;

    QAction* aboutOption;

    QNetworkAccessManager networkMgr;

    QMovie* gearsMovie;

    QMediaPlayer* audioPlayer;

    QList<Course> courses;

    CourseListModel courseModel;

    LessonListModel lessonModel;

};

#endif // APPLICATION_H
