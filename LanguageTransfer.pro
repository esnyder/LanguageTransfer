#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T13:57:32
#
#-------------------------------------------------

QT       += core gui sql network multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LanguageTransfer
TEMPLATE = app


SOURCES += main.cpp\
        application.cpp \
    splashstate.cpp \
    applicationhandler.cpp \
    applicationstatemachine.cpp \
    coursestate.cpp \
    lessonstate.cpp \
    playerstate.cpp \
    applicationstate.cpp \
    lessonwidget.cpp \
    lessonlistmodel.cpp \
    courselistmodel.cpp \
    lessondelegate.cpp \
    clickablelabel.cpp \
    databasemgr.cpp \
    notesstate.cpp \
    coursewidget.cpp \
    coursedelegate.cpp \
    clickablesvgwidget.cpp

HEADERS  += application.h \
    statemachine.h \
    state.h \
    splashstate.h \
    applicationhandler.h \
    applicationstatemachine.h \
    applicationstate.h \
    coursestate.h \
    lessonstate.h \
    playerstate.h \
    lessonwidget.h \
    lessonlistmodel.h \
    courselistmodel.h \
    lessondelegate.h \
    clickablelabel.h \
    databasemgr.h \
    notesstate.h \
    coursewidget.h \
    coursedelegate.h \
    clickablesvgwidget.h

FORMS    += application.ui \
    lessonwidget.ui \
    coursewidget.ui

RESOURCES += \
    resources.qrc

# Needed this to get the database to work on Android for some reason
deployment.files += language_transfer.db
deployment.path = /assets/db
INSTALLS += deployment
