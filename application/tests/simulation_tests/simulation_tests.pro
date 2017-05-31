#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T23:16:40
#
#-------------------------------------------------

QT       += testlib core

QT       -= gui

TARGET = tst_simulation_handler_tests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += ../../src/utility/utility.cpp \
    ../../src/xfoil/simulation.cpp \
    tst_simulation_handler_tests.cpp \
    ../../src/optimizer/geometry.cpp \
    ../../src/xfoil/qsimulation.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../src

HEADERS += \
    ../../src/xfoil/simulation.h \
    ../../src/xfoil/qsimulation.h \
    ../../src/xfoil/simulation_results.h\
    ../../src/xfoil/simulation_proxy.h \
    ../../src/utility/utility.h \
    ../../src/optimizer/geometry.h \
    ../../src/utility/config.h
