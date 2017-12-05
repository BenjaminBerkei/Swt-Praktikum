#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T21:38:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleIsle
TEMPLATE = app


SOURCES += main.cpp\
        startmenuewidget.cpp \
    hexagonbase.cpp \
    button.cpp \
    hexagonmatchfield.cpp \
    matchfield.cpp

HEADERS  += startmenuewidget.h \
    hexagonbase.h \
    button.h \
    enumerations.h \
    hexagonmatchfield.h \
    matchfield.h

FORMS    += startmenuewidget.ui \
    matchfield.ui
