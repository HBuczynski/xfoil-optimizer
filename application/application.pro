TEMPLATE = app

INCLUDEPATH += src
QT += qml quick core gui
QT += charts


CONFIG += c++11
SOURCES += \
    src/gui/view.cpp \
    src/model/model.cpp \
    src/utility/log_writer.cpp \
    src/utility/time_manager.cpp \
    src/main.cpp \
    src/utility/utility.cpp \
    src/gui/settings_dialog.cpp \
    src/gui/plot_dialog.cpp

RESOURCES += src/gui/qml_files/qml.qrc \
    src/gui/qml_files/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/gui/gui_objects.h \
    src/gui/view.h \
    src/model/model.h \
    src/model/profile_parameters.h \
    src/optimizer/genetic.h \
    src/optimizer/genetic_datatypes.h \
    src/utility/configuration_reader.h \
    src/utility/log_writer.h \
    src/utility/time_manager.h \
    src/utility/utility.h \
    src/xfoil/simulation.h \
    src/optimizer/airfoil_optimizer.h \
    src/optimizer/geometry.h \
    src/utility/config.h \
    src/xfoil/simulation_results.h \
    src/gui/settings_dialog.h \
    src/gui/plot_dialog.h

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

win64 { # For Windows
  QMAKE_CXXFLAGS += -openmp
  QMAKE_CXXFLAGS += -arch:AVX
  QMAKE_CXXFLAGS += -D "_CRT_SECURE_NO_WARNINGS"
  QMAKE_CXXFLAGS_RELEASE *= -O2
}

linux { # For Linux
  QMAKE_CXXFLAGS += -fopenmp
  QMAKE_LFLAGS += -fopenmp
  QMAKE_CXXFLAGS += -mavx
  QMAKE_CXXFLAGS_RELEASE *= -O3
}

