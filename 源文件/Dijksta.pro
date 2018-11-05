TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Graph.cpp \
    read.cpp \
    Group.cpp \
    write.cpp

HEADERS += \
    Graph.h \
    read.h \
    request.h \
    Group.h \
    write.h
