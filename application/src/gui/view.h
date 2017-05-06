#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "model/profile_parameters.h"
#include "model/model.h"
#include "gui/settings_dialog.h"


class View : public QObject
{
    Q_OBJECT

public:
    explicit View(Model *model);
	~View();

signals:
    void setBaseProfileValues(AviationProfileParameters data);
    void setTargetProfileValues(AviationProfileParameters data);

public slots:
    void drawBaseChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void drawOptimizedChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void buttonsClicked(QString);
    void getFitnessParametersLabel(AviationProfileParameters data);

	
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

    void getFilePath();

    void initializeModelViewConnection();

    QQmlApplicationEngine engine_;
    QQmlComponent *componentMainWindow_;

    SettingsDialog settingDialog_;
    QString baseFilePath_;


    Model *model_;
    MainWindowObjects guiObjects_;
    AviationProfileParameters baseParameters_;
    AviationProfileParameters targetParameters_;
};
