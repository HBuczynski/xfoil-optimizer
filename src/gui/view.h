#pragma once

#include<profile_parameters.h>
#include<gui_objects.h>
#include<model.h>

class View
{
public:
	View(Model *model);
	~View();

	AviationProfileParameters getInitialProfileParameters();
	void drawChart(std::vector<double> dataX, std::vector<double> dataY);
	
private:
	void initializeGuiObjects();
	void destroyGuiObjects();

	Model *model_;
	GuiObjects guiObjects_;
	AviationProfileParameters profileParameters_;
};