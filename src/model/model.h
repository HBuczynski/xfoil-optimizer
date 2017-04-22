#pragma once

#include<vector>
#include<profile_parameters.h>

class Model
{
public:
	Model();
	~Model();
	
	void initializeLogger();
	void initializeConfigurationReader();

	void setProfileData(AviationProfileParameters data);
	void updateChart(std::vector<double> dataX, std::vector<double> dataY);
};