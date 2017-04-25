#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "src/model/profile_parameters.h"
#include "src/gui/gui_objects.h"
#include "src/model/model.h"

class View : public QObject
{
    Q_OBJECT

public:
    explicit View(Model *model);
	~View();

    const AviationProfileParameters& getInitialProfileParameters();
    void drawChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
	
private:
	void initializeGuiObjects();
    void initializeButtons();
    void initializeBaseParametersLabels();
    void initializeTargetValuesFields();
    void initializeFitnessParametersLabels();
    void initializeChartsFrames();
    void initializeBusyIndicator();

    void initializeModelViewConnection();
	void destroyGuiObjects();

    QQmlApplicationEngine engine_;
    QQmlComponent *componentMainWindow_;

    Model *model_;
	GuiObjects guiObjects_;
	AviationProfileParameters profileParameters_;
};
