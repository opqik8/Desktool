#-------------------------------------------------
#
# Project created by QtCreator 2019-05-14T17:01:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktool
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


SOURCES += \
        main.cpp \
        mainoperate.cpp \
        lowermenu.cpp \
        tool.cpp \
        wallpaper.cpp \
        hotkey.cpp

HEADERS += \
        mainoperate.h \
        lowermenu.h \
        tool.h \
        wallpaper.h \
        hotkey.h

FORMS += \
        mainoperate.ui \
        lowermenu.ui \
        wallpaper.ui


LIBS += -lUser32

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS  +=  /std:c++11
