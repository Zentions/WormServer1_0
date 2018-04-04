#-------------------------------------------------
#
# Project created by QtCreator 2018-03-24T11:12:39
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WormServer1_0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algo.cpp \
    cmdthread.cpp \
    interface.cpp \
    mapthread.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    algo.h \
    cmdthread.h \
    consts.h \
    interface.h \
    mapthread.h \
    form.h
FORMS    += mainwindow.ui \
    form.ui
