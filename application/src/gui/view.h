#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "model/profile_parameters.h"
#include "model/model.h"
#include "gui/settings_dialog.h"
#include "gui/plot_dialog.h"


class View : public QObject
{
    Q_OBJECT

public:
    explicit View(Model *model);

    void enableProgressBar();
    void disableProgressBar();

	~View();

signals:
    void setTargetProfileValues(AviationProfileParameters data);
    void redirectPathToBaseProfile(std::string path);
    void stopSimulation();

public slots:
    void drawBaseChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void drawOptimizedChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void drawGeneticPlot(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void buttonsClicked(QString name);
    void getFitnessParametersLabel(AviationProfileParameters data);
    void getBaseProfileValues(AviationProfileParameters data);
    void setOptimizerSettings();

private:
	void initializeGuiObjects();
    void initializeMainWindow();
    void initializeButtons();
    void initializeBaseParametersLabels();
    void initializeTargetValuesFields();
    void initializeFitnessParametersLabels();
    void initializeChartsFrames();
    void initializeBusyIndicator();
    void initializeOptimizerSettings();
    void initializePlotDialog();

    void initializeModelViewConnection();
    bool checkIfTargetIsSet();

    void setFilePath();

    QQmlApplicationEngine engine_;
    QQmlComponent *componentMainWindow_;

    SettingsDialog settingDialog_;
    PlotDialog plotDialog_;

    Model *model_;
    MainWindowObjects guiObjects_;
    AviationProfileParameters baseParameters_;
    AviationProfileParameters targetParameters_;
};
