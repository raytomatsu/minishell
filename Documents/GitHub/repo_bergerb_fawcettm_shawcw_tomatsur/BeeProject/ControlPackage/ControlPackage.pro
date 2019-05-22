TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sense.cpp \
    hive.cpp \
    controller.cpp \
    query.cpp \
    event.cpp \
    hivecontainer.cpp \
    activitycontainer.cpp \
    activity.cpp \
    decoder.cpp \
    udpmessage.cpp \
    eventcontainer.cpp

HEADERS += \
    sense.h \
    hive.h \
    controller.h \
    query.h \
    event.h \
    hivecontainer.h \
    activitycontainer.h \
    activity.h  \
    decoder.h \
    udpmessage.h \
    eventcontainer.h

SOURCES += \
    ../DBPackage/dbtool.cpp \
    ../DBPackage/dbtable.cpp \
    ../DBPackage/dbhive.cpp \
    ../DBPackage/dbconfiguration.cpp \
    ../DBPackage/dbevent.cpp \
    #../DBPackage/sqlite3.c \


HEADERS += \
    ../DBPackage/dbtool.h \
    ../DBPackage/dbtable.h \
    ../DBPackage/dbhive.h \
    ../DBPackage/dbconfiguration.h \
    ../DBPackage/dbevent.h \
   # ../DBPackage/sqlite3.h \



LIBS += -l sqlite3
