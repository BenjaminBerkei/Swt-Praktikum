#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T17:39:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matchfield
TEMPLATE = app


SOURCES += main.cpp\
        matchfield.cpp \
    button.cpp \
    hexagonbase.cpp \
    hexagonmatchfield.cpp

HEADERS  += matchfield.h \
    button.h \
    enumerations.h \
    hexagonbase.h \
    hexagonmatchfield.h

FORMS    += matchfield.ui
CONFIG += c++11
