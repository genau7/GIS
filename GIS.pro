QT += core
QT -= gui

TARGET = GIS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    graph.cpp \
    util.cpp \
    search.cpp \
    result.cpp

HEADERS += \
    graph.h \
    util.h \
    search.h \
    result.h

