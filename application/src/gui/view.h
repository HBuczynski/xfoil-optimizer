#pragma once

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "model/profile_parameters.h"
#include "gui/gui_objects.h"
#include "model/model.h"

class View
{
public:
    View();
	~View();

	AviationProfileParameters getInitialProfileParameters();
	void drawChart(std::vector<double> dataX, std::vector<double> dataY);
	
private:
	void initializeGuiObjects();
	void destroyGuiObjects();

    QQmlApplicationEngine engine;

	Model *model_;
	GuiObjects guiObjects_;
	AviationProfileParameters profileParameters_;
};
