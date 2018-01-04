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
    hexagonbase.cpp \
    button.cpp \
    hexagonmatchfield.cpp \
    matchfield.cpp \
    options.cpp \
    savegame.cpp \
    optionswidget.cpp \
    menuewidget.cpp \
    startmenuewidget.cpp \
    loadgamewidget.cpp \
    gamewidget.cpp \
    game.cpp

HEADERS  += \
    hexagonbase.h \
    button.h \
    enumerations.h \
    hexagonmatchfield.h \
    matchfield.h \
    options.h \
    savegame.h \
    optionswidget.h \
    menuewidget.h \
    startmenuewidget.h \
    loadgamewidget.h \
    gamewidget.h \
    game.h

FORMS    += startmenuewidget.ui \
    matchfield.ui \
    optionswidget.ui \
    menuewidget.ui \
    startmenuewidget.ui \
    loadgamewidget.ui \
    gamewidget.ui

RESOURCES += \
    img/rsc.qrc

CONFIG += c++11
