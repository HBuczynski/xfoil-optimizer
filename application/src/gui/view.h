#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "model/profile_parameters.h"
#include "gui/gui_objects.h"
#include "model/model.h"

class View : public QObject
{
    Q_OBJECT

public:
    explicit View(Model *model);
	~View();

    const AviationProfileParameters& getInitialProfileParameters();

signals:
    void setBaseProfileVlues(AviationProfileParameters data);
    void setTargetProfileValues(AviationProfileParameters data);

public slots:
    void drawChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
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

    void initializeModelViewConnection();

    QQmlApplicationEngine engine_;
    QQmlComponent *componentMainWindow_;

    Model *model_;
	GuiObjects guiObjects_;
	AviationProfileParameters profileParameters_;
};
