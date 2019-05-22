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
    ../DecodeUDPMessages/hivecontainer.cpp \
    ../DecodeUDPMessages/activitycontainer.cpp \
    ../DecodeUDPMessages/hive.cpp \
    ../DecodeUDPMessages/activity.cpp
    #sqlite3.c

HEADERS += \
    dbtool.h \
    dbtable.h \
    dbhive.h \
    dbconfiguration.h \
    ../DecodeUDPMessages/hivecontainer.h \
    ../DecodeUDPMessages/activitycontainer.h \
    ../DecodeUDPMessages/hive.h \
    ../DecodeUDPMessages/activity.h
    #sqlite3.h

LIBS += -l sqlite3
