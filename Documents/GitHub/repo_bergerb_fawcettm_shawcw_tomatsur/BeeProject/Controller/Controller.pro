TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QT +=core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
        main.cpp \
        ../GUI/mainwindow.cpp
        ../GUI/hiveowner.cpp \
        ../GUI/researcher.cpp \
    #teacher.cpp \
        ../GUI/requestinfo.cpp \
        ../GUI/confighive.cpp \
        ../GUI/updatehive.cpp

HEADERS += \
        ../GUI/mainwindow.h \
        ../GUI/hiveowner.h \
        ../GUI/researcher.h \
    #teacher.h \
        ../GUI/requestinfo.h \
        ../GUI/confighive.h \
        ../GUIupdatehive.h

FORMS += \
        ../GUI/mainwindow.ui \
    ../GUI/hiveowner.ui \
    ../GUI/researcher.ui \
    #teacher.ui \
    ../GUI/requestinfo.ui \
    ../GUI/confighive.ui \
    ../GUIupdatehive.ui


