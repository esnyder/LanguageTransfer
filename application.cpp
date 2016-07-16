#include <QMenu>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDesktopServices>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFontDatabase>
#include <QScreen>
#include "splashstate.h"
#include "application.h"
#include "lessonwidget.h"
#include "coursedelegate.h"
#include "lessondelegate.h"
#include "clickablesvgwidget.h"
#include "ui_application.h"


//--------------------------------------------------------------------------------------
Application::Application(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Application),
    stateMachine(new ApplicationStateMachine(this)),
    gearsMovie(new QMovie(":/movies/gears.gif")),
    audioPlayer(new QMediaPlayer(this))
{
    QFontDatabase fontDB;
    fontDB.addApplicationFont(":/fonts/Roboto-Regular.ttf");

    ui->setupUi(this);
    ui->banner->setFont(QFontDatabase().font("Roboto", "Regular", 20));
    ui->startTime->setFont(QFontDatabase().font("Roboto", "Regular", 14));
    ui->endTime->setFont(QFontDatabase().font("Roboto", "Regular", 14));
    ui->notesTextEdit->setFont(QFontDatabase().font("Roboto", "Regular", 16));
    ui->notesSaveStatusLabel->setFont(QFontDatabase().font("Roboto", "Regular", 14));

    ui->courseListView->setModel(&courseModel);
    ui->lessonListView->setModel(&lessonModel);

    ui->backButton->setIcon(":/images/arrow-left.svg", QSize(24, 24));
    ui->backButton->setStyleSheet("background-color: black;");

    ui->optionsButton->setIcon(":/images/more-vertical.svg", QSize(24, 24));
    ui->optionsButton->setStyleSheet("background-color: black;");

    setFixedSize(qApp->primaryScreen()->size());

    CourseDelegate* courseDelegate = new CourseDelegate(&courseModel);
    ui->courseListView->setItemDelegate(courseDelegate);

    LessonDelegate* lessonDelegate = new LessonDelegate(&lessonModel);
    ui->lessonListView->setItemDelegate(lessonDelegate);

    // Start the movie even though we won't be able to see it. Otherwise,
    // the label doesn't properly resize to hold the gif until the user
    // hits play the first time:
    ui->gearsLabel->setMovie(gearsMovie);
    gearsMovie->setSpeed(25);
    gearsMovie->start();

    // Most user interface signals should be handed off to the application's
    // state machine so that it, in turn, can pass the signals onto its
    // current state:
    connect(courseDelegate, SIGNAL(courseClicked(QModelIndex)),
            stateMachine, SLOT(courseClicked(QModelIndex)));
    connect(lessonDelegate, SIGNAL(lessonClicked(QModelIndex)),
            stateMachine, SLOT(lessonClicked(QModelIndex)));
    connect(lessonDelegate, SIGNAL(notesButtonClicked(QModelIndex)),
            stateMachine, SLOT(notesButtonClicked(QModelIndex)));
    connect(ui->notesTextEdit, SIGNAL(textChanged()),
            stateMachine, SLOT(notesChanged()));
    connect(ui->backButton, SIGNAL(clicked()),
            stateMachine, SLOT(backButtonClicked()));
    connect(this, SIGNAL(backButtonReleased()),
            stateMachine, SLOT(backButtonClicked()));
    connect(ui->gearsLabel, SIGNAL(clicked()),
            stateMachine, SLOT(playButtonClicked()));
    connect(ui->seekSlider, SIGNAL(sliderMoved(int)),
            stateMachine, SLOT(sliderMoved(int)));
    connect(ui->seekSlider, SIGNAL(sliderReleased()),
            stateMachine, SLOT(sliderReleased()));
    connect(audioPlayer, SIGNAL(durationChanged(qint64)),
            stateMachine, SLOT(trackDurationChanged(qint64)));
    connect(audioPlayer, SIGNAL(positionChanged(qint64)),
            stateMachine, SLOT(trackPositionChanged(qint64)));

    // Setup the options menu by adding various actions:
    QMenu* optionsMenu = new QMenu(this);
    //ui->optionsButton->setMenu(optionsMenu);
    //optionsMenu->setStyleSheet("QMenu{background: white; border-radius: 2px; color: black; height: 100px;}\nQMenu::item{padding: 8px;}");
    optionsMenu->setFont(QFontDatabase().font("Roboto", "Regular", 14));

    homeOption = new QAction("LT home", this);
    connect(homeOption, SIGNAL(triggered(bool)),
            this, SLOT(openMenu()));
    optionsMenu->addAction(homeOption);

    patronOption = new QAction("Become a patron", this);
    connect(patronOption, SIGNAL(triggered(bool)),
            this, SLOT(openMenu()));
    optionsMenu->addAction(patronOption);

    aboutOption = new QAction("About", this);
    connect(aboutOption, SIGNAL(triggered(bool)),
            this, SLOT(openMenu()));
    optionsMenu->addAction(aboutOption);

    // Set the application's initial state, its splash screen state:
    stateMachine->transition(new SplashState(this));
}


//--------------------------------------------------------------------------------------
Application::~Application()
{
    delete ui;
    delete gearsMovie;
}


//--------------------------------------------------------------------------------------
Ui::Application* Application::getUserInterface() const
{
    return ui;
}


//--------------------------------------------------------------------------------------
QMovie* Application::getGearsMovie() const
{
    return gearsMovie;
}


//--------------------------------------------------------------------------------------
QMediaPlayer* Application::getAudioPlayer() const
{
    return audioPlayer;
}


//--------------------------------------------------------------------------------------
const QList<Course>& Application::getCourses() const
{
    return courses;
}


//--------------------------------------------------------------------------------------
Course Application::getCourse(const QModelIndex& index) const
{
    return courseModel.getCourseId(index);
}


//--------------------------------------------------------------------------------------
Lesson Application::getLesson(const QModelIndex& index) const
{
    return lessonModel.getLessonId(index);
}


//--------------------------------------------------------------------------------------
void Application::transition(ApplicationState* state)
{
    stateMachine->transition(state);
}


//--------------------------------------------------------------------------------------
void Application::initializeDatabase()
{
    // Creating the data base manager creates the database:
    DatabaseMgr::Instance();

    // Setup a network manager:
    networkMgr.setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(&networkMgr, SIGNAL(finished(QNetworkReply*)),
            stateMachine, SLOT(playListRequestFinished(QNetworkReply*)), Qt::UniqueConnection);

    // Ask SoundCloud for information about LT's playlists:
    QString playlistPath = "http://api.soundcloud.com/users/81304541/playlists.json";
    AppendClientId(playlistPath);
    QUrl url(playlistPath);
    networkMgr.get( QNetworkRequest(url) );
}


//--------------------------------------------------------------------------------------
void Application::populateDatabase(QNetworkReply* reply)
{
    // Assuming no errors, SoundCloud has returned JSON that contains information about
    // LT's playlists, including each playlist's tracks:
    if(reply->error() == QNetworkReply::NoError)
    {
        // Parse the JSON document as necessary, inserting pertinent data into the db:
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

        QJsonArray playlists = doc.array();
        for(int i = 0; i < playlists.size(); ++i)
        {
            // First, populate the course table:
            QJsonObject playlist = playlists.at(i).toObject();
            int courseID = playlist["id"].toInt();
            QString courseName = playlist["title"].toString();
            QByteArray courseIcon = loadImage(playlist["artwork_url"].toString());

            QSqlDatabase database = DatabaseMgr::Instance()->getDatabase();
            QSqlQuery insertQuery(database);
            insertQuery.prepare((QString("INSERT OR IGNORE INTO COURSE "
                            "(COURSE_ID, NAME, ICON) "
                            "VALUES (%1, '%2', :icon)")
                            .arg(courseID).arg(courseName)));
            insertQuery.bindValue(":icon", courseIcon);
            insertQuery.exec();

            QSqlQuery updateQuery(database);
            updateQuery.prepare((QString("UPDATE COURSE "
                            "SET NAME='%1' "
                            "WHERE COURSE_ID=%2")
                            .arg(courseName).arg(courseID)));
            updateQuery.exec();

            // Now, populate the lesson table:
            QJsonArray tracks = playlist["tracks"].toArray();
            for(int j = 0; j < tracks.size(); ++j)
            {
                QJsonObject track = tracks.at(j).toObject();
                int lessonID = track["id"].toInt();
                QString lessonName = track["title"].toString();
                int duration = track["duration"].toInt();
                database.exec(QString("INSERT OR IGNORE INTO LESSON"
                                "(LESSON_ID, COURSE_ID, NAME, PLAY_TIME, DURATION, BOOKMARKED, FORCIBLY_UNCHECKED)"
                                "VALUES (%1, %2, '%3', 0, %4, 0, 0)")
                                .arg(lessonID).arg(courseID).arg(lessonName).arg(duration));
                database.exec(QString("UPDATE LESSON "
                                      "SET NAME='%1' "
                                      "WHERE LESSON_ID=%2")
                                       .arg(lessonName).arg(lessonID));
            }
        }
    }
    reply->deleteLater();
}


//--------------------------------------------------------------------------------------
void Application::AppendClientId(QString& url)
{
    QFile file(":/config/client_id.config");
    if(file.open(QFile::ReadOnly))
    {
        QString clientId(file.readAll());
        clientId.remove("\n"); // remove trailing new-line character
        if(clientId.isEmpty())
            qWarning("Missing client id. Add your client id to 'client_id.config'.");
        else
            url.append(QString("?client_id=%1").arg(clientId));
    }
    else
    {
        qWarning("Could not read from 'client_id.config'.");
    }
}


//--------------------------------------------------------------------------------------
void Application::openMenu()
{
    QAction* menuAction = dynamic_cast<QAction*>(sender());
    if(menuAction == homeOption)
    {
        QDesktopServices::openUrl(QUrl("http://www.languagetransfer.org/"));
    }
    else if(menuAction == patronOption)
    {
        QDesktopServices::openUrl(QUrl("http://www.languagetransfer.org/#!voting/c1dm6"));
    }
    else if(menuAction == aboutOption)
    {
        QDesktopServices::openUrl(QUrl("http://www.languagetransfer.org/#!about/cfvg"));
    }
    else
    {
        qWarning("Unrecognized option.");
    }
}


//--------------------------------------------------------------------------------------
void Application::setCourses(const QList<int>& ids)
{
    courseModel.setCourses(ids);

    foreach(int id, ids)
    {
        ui->courseListView->openPersistentEditor(
                    courseModel.getIndex(id));
    }
}


//--------------------------------------------------------------------------------------
void Application::setLessons(const QList<int>& ids)
{
    lessonModel.setLessons(ids);

    foreach(int id, ids)
    {
        ui->lessonListView->openPersistentEditor(
                    lessonModel.getIndex(id));
    }
}


//--------------------------------------------------------------------------------------
void Application::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Back)
    {
        event->accept();
        emit backButtonReleased();
    }
    else
    {
        QMainWindow::keyReleaseEvent(event);
    }
}


//--------------------------------------------------------------------------------------
QByteArray Application::loadImage(const QString& urlPath)
{
    QString temp(urlPath);
    temp.replace("https", "http");

    QEventLoop loop;
    QNetworkAccessManager mgr;
    mgr.setNetworkAccessible(QNetworkAccessManager::Accessible);
    connect(&mgr, SIGNAL(finished(QNetworkReply*)),
            &loop, SLOT(quit()));

    QUrl url(temp);
    QNetworkReply* reply = mgr.get( QNetworkRequest(url) );
    loop.exec();

    return reply->readAll();
}
