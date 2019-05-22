#-------------------------------------------------
#
# Project created by QtCreator 2019-04-16T10:00:25
#
#-------------------------------------------------

QT       += core gui network
QT += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = GUI
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
        mainwindow.cpp \
    hiveowner.cpp \
    researcher.cpp \
    #teacher.cpp \
    requestinfo.cpp \
    confighive.cpp \
    #updatehive.cpp \
    displayinfo.cpp \
    qcustomplot.cpp \
    graph.cpp \
    requestinfoonehive.cpp \
    requestgraph.cpp \
    graphsmulti.cpp


HEADERS += \
        mainwindow.h \
    hiveowner.h \
    researcher.h \
    #teacher.h \
    requestinfo.h \
    confighive.h \
    displayinfo.h \
    qcustomplot.h \
    graph.h \
    requestinfoonehive.h \
    requestgraph.h \
    graphsmulti.h


FORMS += \
        mainwindow.ui \
    hiveowner.ui \
    researcher.ui \
    #teacher.ui \
    requestinfo.ui \
    confighive.ui \
    #updatehive.ui \
    displayinfo.ui \
    graph.ui \
    requestinfoonehive.ui \
    requestgraph.ui \
    graphsmulti.ui

SOURCES +=  \
    ../ControlPackage/sense.cpp \
    ../ControlPackage/hive.cpp \
    ../ControlPackage/controller.cpp \
    ../ControlPackage/query.cpp \
    ../ControlPackage/event.cpp \
    ../ControlPackage/hivecontainer.cpp \
    ../ControlPackage/activitycontainer.cpp \
    ../ControlPackage/eventcontainer.cpp \
    ../ControlPackage/activity.cpp \
    ../ControlPackage/decoder.cpp \
    ../ControlPackage/udpmessage.cpp \

HEADERS += \
    ../ControlPackage/sense.h \
    ../ControlPackage/hive.h \
    ../ControlPackage/controller.h \
    ../ControlPackage/query.h \
    ../ControlPackage/event.h \
    ../ControlPackage/hivecontainer.h \
    ../ControlPackage/activitycontainer.h \
    ../ControlPackage/eventcontainer.h \
    ../ControlPackage/activity.h  \
    ../ControlPackage/decoder.h \
    ../ControlPacka ge/udpmessage.h \

SOURCES += \
    ../DBPackage/dbtool.cpp \
    ../DBPackage/dbtable.cpp \
    ../DBPackage/dbhive.cpp \
    ../DBPackage/dbconfiguration.cpp \
    ../DBPackage/dbevent.cpp \
   # ../DBPackage/sqlite3.c \

HEADERS += \
    ../DBPackage/dbtool.h \
    ../DBPackage/dbtable.h \
    ../DBPackage/dbhive.h \
    ../DBPackage/dbconfiguration.h \
    ../DBPackage/dbevent.h \
    #../DBPackage/sqlite3.h \

LIBS += -l sqlite3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    secondresource.qrc

DISTFILES += \
    daisy-flower-with-bee-background-vector-20685265.jpg \
    warning.jpg
