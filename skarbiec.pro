#-------------------------------------------------
#
# Project created by QtCreator 2012-04-25T14:29:03
#
#-------------------------------------------------

QMAKE_CFLAGS = $$system(mpicc --showme:compile)
QMAKE_CXXFLAGS = $$system(mpic++ --showme:compile)
QMAKE_LIBS = $$system(mpic++ --showme:link)

QT       += core

QT       -= gui

TARGET = skarbiec
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mainobject.cpp \
    inputthread.cpp \
    outputthread.cpp

HEADERS += \
    mainobject.hpp \
    inputthread.hpp \
    outputthread.hpp
