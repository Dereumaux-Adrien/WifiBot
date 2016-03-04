#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T15:35:19
#
#-------------------------------------------------

QT       += core gui\
        network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WifiBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socket.cpp

HEADERS  += mainwindow.h \
    socket.h

FORMS    += mainwindow.ui
