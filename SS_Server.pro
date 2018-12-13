#-------------------------------------------------
#
# Project created by QtCreator 2018-03-24T11:12:39
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WormServer1_0
TEMPLATE = app
RC_ICONS = server_icon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    algo.cpp \
    cmdthread.cpp \
    interface.cpp \
    mapthread.cpp \
    appmanagedialog.cpp \
    workpanel.cpp

HEADERS  += mainwindow.h \
    algo.h \
    cmdthread.h \
    consts.h \
    interface.h \
    mapthread.h \
    appmanagedialog.h \
    workpanel.h
FORMS    += mainwindow.ui \
    appmanagedialog.ui \
    workpanel.ui
