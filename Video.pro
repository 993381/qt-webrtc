#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T12:46:06
#
#-------------------------------------------------

#QT       += core gui
#QT += webenginewidgets
QT += webenginewidgets serialport
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Video
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    video.cpp

HEADERS  += mainwindow.h \
    video.h

FORMS    += mainwindow.ui
