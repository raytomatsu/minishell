#-------------------------------------------------
#
# Project created by QtCreator 2019-04-25T10:20:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Control
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        #mainwindow.cpp\
        ../GUIPackage/mainwindow.cpp   \
        ../GUIPackage/hiveowner.cpp \
        ../GUIPackage/researcher.cpp \
    #teacher.cpp \
        ../GUIPackage/requestinfo.cpp \
        ../GUIPackage/confighive.cpp \
        ../GUIPackage/updatehive.cpp \
    dbconnector.cpp

HEADERS += \
        #mainwindow.h    \
         ../GUIPackage/mainwindow.h \
        ../GUIPackage/hiveowner.h \
        ../GUIPackage/researcher.h \
    #teacher.h \
        ../GUIPackage/requestinfo.h \
        ../GUIPackage/confighive.h \
        ../GUIPackage/updatehive.h \
    dbconnector.h

FORMS += \
        #mainwindow.ui   \
       ../GUIPackage/mainwindow.ui \
    ../GUIPackage/hiveowner.ui \
    ../GUIPackage/researcher.ui \
    #teacher.ui \
    ../GUIPackage/requestinfo.ui \
    ../GUIPackage/confighive.ui \
    ../GUIPackage/updatehive.ui

SOURCES += \
    ../DBPackage/dbtool.cpp \
    ../DBPackage/dbtable.cpp \
    ../DBPackage/dbhive.cpp \
    ../DBPackage/dbconfiguration.cpp \
    ../DBPackage/sqlite3.c

HEADERS += \
    ../DBPackage/dbtool.h \
    ../DBPackage/dbtable.h \
    ../DBPackage/dbhive.h \
    ../DBPackage/dbconfiguration.h \
    ../DBPackage/sqlite3.h

SOURCES +=\
    ../Controlpackage/sense.cpp \
    ../Controlpackage/hive.cpp \
    ../Controlpackage/controller.cpp \
    ../Controlpackage/query.cpp \
    ../Controlpackage/event.cpp \
    ../Controlpackage/hivecontainer.cpp \
    ../Controlpackage/activitycontainer.cpp \
    ../Controlpackage/activity.cpp  \
    ../Controlpackage/decoder.cpp

HEADERS += \
    ../Controlpackage/sense.h \
    ../Controlpackage/hive.h \
    ../Controlpackage/controller.h \
    ../Controlpackage/query.h \
    ../Controlpackage/event.h \
    ../Controlpackage/hivecontainer.h \
    ../Controlpackage/activitycontainer.h \
    ../Controlpackage/activity.h    \
    ../Controlpackage/decoder.h

#LIBS += -l sqlite3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    ../GUIPackage/resource.qrc

