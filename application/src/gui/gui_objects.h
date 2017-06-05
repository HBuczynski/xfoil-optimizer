#pragma once

#include <QObject>
#include <QDialog>
#include <vector>


/**
*	@file gui_objects.h
*	@brief This header file contains all required objects represents user interface.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

struct Component
{
    QObject *object;
    std::string name;
};

struct MainWindowObjects
{
    QObject* mainWindow;
    Component settingsButtonsRoot;
    Component baseParametersRoot;
    Component targetValuesRoot;
    Component fitnessValuesRoot;

    Component baseChartFrame;
    Component optimizeChartFrame;
    Component busyIndicator;

    QObject* basePlot;
    QObject* optimizedPlot;
    QObject* runButton;
    QObject* stopButton;

    std::vector<QObject*> settingsButtons;
    std::vector<QObject*> baseParameters;
    std::vector<QObject*> targetValues;
    std::vector<QObject*> fitnessValues;

    QObject* optimizerSettings;

    const int buttonsCount = 3;
    const int parametersLabelCount = 3;

    bool SET_TARGET = false;
    bool SET_BASE = false;
    bool RUN_BUTTON_IS_PRESSED = false;
};

struct SettingsObjects
{
    QObject* settingsWindow;
    QObject* windowFrame;
    QObject* applyButton;
    QObject* cancelButton;

    QObject* generationCount;
    QObject* populationSize;
    QObject* muatationRate;
};

struct Plot
{
    QObject* plotWindow;
    QObject* plotFrame;
    QObject* plot;
};
