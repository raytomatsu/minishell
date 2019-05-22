TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    dbtool.cpp \
    dbtable.cpp \
    dbhive.cpp \
    dbconfiguration.cpp \
    ../ControlPackage/hivecontainer.cpp \
    ../ControlPackage/activitycontainer.cpp \
    ../ControlPackage/eventcontainer.cpp \
    ../ControlPackage/event.cpp \
    ../ControlPackage/hive.cpp \
    ../ControlPackage/activity.cpp \
    dbevent.cpp \
    #sqlite3.c

HEADERS += \
    dbtool.h \
    dbtable.h \
    dbhive.h \
    dbconfiguration.h \
    ../ControlPackage/hivecontainer.h \
    ../ControlPackage/activitycontainer.h \
    ../ControlPackage/eventcontainer.h \
    ../ControlPackage/event.h \
    ../ControlPackage/hive.h \
    ../ControlPackage/activity.h \
    dbevent.h \
    #sqlite3.h

LIBS += -l sqlite3
