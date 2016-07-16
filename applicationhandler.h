#ifndef APPLICATIONHANDLER_H
#define APPLICATIONHANDLER_H

#include <QObject>
#include <QNetworkReply>
#include <QListWidgetItem>

class ApplicationHandler : public QObject
{

    Q_OBJECT

public:
    ApplicationHandler(QObject* parent = 0);

public slots:
    virtual void playListRequestFinished(QNetworkReply* reply) { Q_UNUSED(reply); }

    virtual void backButtonClicked() {}

    virtual void courseClicked(const QModelIndex& index) { Q_UNUSED(index); }

    virtual void lessonClicked(const QModelIndex& index) { Q_UNUSED(index); }

    virtual void notesButtonClicked(const QModelIndex& index) { Q_UNUSED(index); }

    virtual void notesChanged() {}

    virtual void playButtonClicked() {}

    virtual void sliderMoved(int position) { Q_UNUSED(position); }

    virtual void sliderReleased() {}

    virtual void trackDurationChanged(qint64 duration) { Q_UNUSED(duration); }

    virtual void trackPositionChanged(qint64 position) { Q_UNUSED(position); }

};

#endif // APPLICATIONHANDLER_H
