#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T21:34:09
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_qsimulation_proxy_tests
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


SOURCES +=  ../../src/xfoil/simulation.cpp ../../src/xfoil/qsimulation.cpp \
            tst_qsimulationproxy_tests.cpp \
    ../../src/utility/utility.cpp \
    ../../src/optimizer/geometry.cpp \
    ../../src/optimizer/simulation_results.cpp \
    ../../src/optimizer/genetic/fitness.cpp \
    ../../src/optimizer/genetic/genetic.cpp \
    ../../src/optimizer/genetic/genome.cpp \
    ../../src/optimizer/genetic/genome_scrambler.cpp

INCLUDEPATH += ../../src
win32 {
    INCLUDEPATH += C:/boost_1_55_0
}
win64 {
    #INCLUDEPATH += C:/boost_1_55_0
}
linux { # For Linux
    LIBS += -lboost_system
}
INCLUDEPATH += C:/boost_1_55_0
HEADERS += \
    ../../src/xfoil/simulation.h \
    ../../src/xfoil/qsimulation.h \
    ../../src/optimizer/simulation_results.h \
    ../../src/xfoil/simulation_proxy.h \
    ../../src/optimizer/airfoil_optimizer.h \
    ../../src/optimizer/geometry.h \
    ../../src/optimizer/geometry_structures.h \
    ../../src/optimizer/genetic/fitness.h \
    ../../src/optimizer/genetic/genetic.h \
    ../../src/optimizer/genetic/genome.h \
    ../../src/optimizer/genetic/genome_scrambler.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
