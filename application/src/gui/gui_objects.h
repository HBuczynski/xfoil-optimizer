#pragma once

#include <QObject>
#include <QDialog>
#include <vector>

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

    std::vector<QObject*> settingsButtons;
    std::vector<QObject*> baseParameters;
    std::vector<QObject*> targetValues;
    std::vector<QObject*> fitnessValues;

    QObject* optimizerSettings;

    const int buttonsCount = 3;
    const int parametersLabelCount = 3;

    bool SET_TARGET = false;
    bool SET_BASE = false;
};

struct SettingsObjects
{
    QObject* settingsWindow;
};
