#-------------------------------------------------
#
# Project created by QtCreator 2017-06-02T14:06:24
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_configreadertest
CONFIG   += console
CONFIG   -= app_bundle

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

INCLUDEPATH += ../../src
win32 {
    INCLUDEPATH += C:/boost_1_55_0
}
linux { # For Linux
    QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
    QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0
    LIBS += -lboost_system \
            -lgcov
}
SOURCES += tst_configreadertest.cpp \
    ../../src/utility/configuration_reader.cpp \
    ../../src/utility/tiny_xml/tinystr.cpp \
    ../../src/utility/tiny_xml/tinyxml.cpp \
    ../../src/utility/tiny_xml/tinyxmlerror.cpp \
    ../../src/utility/tiny_xml/tinyxmlparser.cpp \
    ../../src/utility/log_writer.cpp \
    ../../src/utility/time_manager.cpp \
    ../../src/utility/utility.cpp \
    ../../src/optimizer/geometry.cpp \
    ../../src/optimizer/simulation_results.cpp \
    ../../src/optimizer/genetic/fitness.cpp \
    ../../src/optimizer/genetic/genetic.cpp \
    ../../src/optimizer/genetic/genome.cpp \
    ../../src/optimizer/genetic/genome_scrambler.cpp \
    ../../src/xfoil/qsimulation.cpp \
    ../../src/xfoil/simulation.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/utility/config.h \
    ../../src/utility/configuration_reader.h \
    ../../src/utility/tiny_xml/tinystr.h \
    ../../src/utility/tiny_xml/tinyxml.h \
    ../../src/utility/log_writer.h \
    ../../src/utility/time_manager.h \
    ../../src/utility/utility.h \
    ../../src/optimizer/airfoil_optimizer.h \
    ../../src/optimizer/geometry.h \
    ../../src/optimizer/geometry_structures.h \
    ../../src/optimizer/simulation_results.h \
    ../../src/optimizer/genetic/fitness.h \
    ../../src/optimizer/genetic/genetic.h \
    ../../src/optimizer/genetic/genome.h \
    ../../src/optimizer/genetic/genome_scrambler.h \
    ../../src/xfoil/qsimulation.h \
    ../../src/xfoil/simulation.h \
    ../../src/xfoil/simulation_proxy.h
