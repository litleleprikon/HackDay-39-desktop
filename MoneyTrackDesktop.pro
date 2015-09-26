#-------------------------------------------------
#
# Project created by QtCreator 2015-09-25T21:17:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoneyTrackDesktop
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    screenshot.cpp \
    grabber.cpp \
    winapi.cpp \
    xlib.cpp

HEADERS  += window.h \
    screenshot.h \
    grabber.h \
    winapi.h \
    xlib.h

FORMS    += window.ui
