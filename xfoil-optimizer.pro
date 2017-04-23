# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = xfoil-optimizer

HEADERS = \
   $$PWD/src/gui/gui_objects.h \
   $$PWD/src/gui/view.h \
   $$PWD/src/model/model.h \
   $$PWD/src/model/profile_parameters.h \
   $$PWD/src/optimizer/genetic.h \
   $$PWD/src/optimizer/genetic_datatypes.h \
   $$PWD/src/utility/configuration_reader.h \
   $$PWD/src/utility/log_writer.h \
   $$PWD/src/utility/time_manager.h \
   $$PWD/src/utility/utility.h \
   $$PWD/src/xfoil/simulation.h

SOURCES = \
   $$PWD/src/utility/log_writer.cpp \
   $$PWD/src/utility/time_manager.cpp \
   $$PWD/src/main.cpp

INCLUDEPATH = \
    $$PWD/src/gui \
    $$PWD/src/model \
    $$PWD/src/optimizer \
    $$PWD/src/utility \
    $$PWD/src/xfoil

#DEFINES = 

