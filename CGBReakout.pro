#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T13:26:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGBReakout
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../Common.pri)

SOURCES += \
    Brick.cpp \
    Ball.cpp \
    main.cpp \
    GameObject.cpp \
    Platform.cpp \
    FixedCamera.cpp \
    Game.cpp \
    ItemDrop.cpp \
    GeometryHandler.cpp \
    ItemDropDrawable.cpp \
    HUDElement.cpp \
    HUDHeart.cpp

HEADERS += \
    Brick.h \
    Ball.h \
    GameObject.h \
    Platform.h \
    FixedCamera.h \
    Game.h \
    ItemDrop.h \
    GeometryHandler.h \
    ItemDropDrawable.h \
    HUDElement.h \
    HUDHeart.h

FORMS += \
    dockwidget.ui
