TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    udpmessage.cpp \
    ../DBPackage/dbtool.cpp \
    ../DBPackage/dbtable.cpp \
    ../DBPackage/dbhive.cpp \
    #../DBPackage/sqlite3.c \
    ../ControlPackage/activitycontainer.cpp \
    ../ControlPackage/activity.cpp


HEADERS += \
    udpmessage.h \
    ../DBPackage/dbtool.h \
    ../DBPackage/dbtable.h \
    ../DBPackage/dbhive.h \
    #../DBPackage/sqlite3.h \
    ../ControlPackage/activitycontainer.h \
    ../ControlPackage/activity.h


LIBS += -l sqlite3
