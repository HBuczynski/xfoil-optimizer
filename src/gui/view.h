#pragma once

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/model/profile_parameters.h"
#include "src/gui/gui_objects.h"
#include "src/model/model.h"

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
