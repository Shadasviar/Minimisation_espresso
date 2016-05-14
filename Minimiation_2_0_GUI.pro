#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T18:13:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minimiation_2_0_GUI
TEMPLATE = app

QMAKE_CXXFLAGS += -g


SOURCES += main.cpp\
        mainwindow.cpp \
    espresso.cpp \
    matrix.cpp \
    filename_enter.cpp

HEADERS  += mainwindow.h \
    espresso.h \
    matrix.h \
    to_binary.h \
    filename_enter.h

FORMS    += mainwindow.ui \
    filename_enter.ui

CONFIG += console c++11
CONFIG -= app_bundle

