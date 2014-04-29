#-------------------------------------------------
#
# Project created by QtCreator 2014-04-18T16:50:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = PupilTracking
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    PupilDetection_Hough_Circular.cpp

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += `pkg-config opencv --libs`

HEADERS += \
    PupilDetection_Hough_Circular.h
