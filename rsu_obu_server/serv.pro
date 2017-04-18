TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    unpackage.cpp \
    serv_main.cpp \
    serv.cpp

HEADERS += \
    unpackage.h \
    tcp.h
