QT += core
QT -= gui

TARGET = GIS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    graph.cpp \
    util.cpp

HEADERS += \
    graph.h \
    util.h

