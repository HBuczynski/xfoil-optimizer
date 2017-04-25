#pragma once

#include <vector>
#include "src/model/profile_parameters.h"
#include "utility/log_writer.h"

class Model
{
public:
	Model();
	~Model();

    void setProfileData(AviationProfileParameters &data);
	void updateChart(std::vector<double> dataX, std::vector<double> dataY);

private:
	void initializeLogger();
	void initializeConfigurationReader();

    AviationProfileParameters baseProfileData_;
    LogWriter *logger_;

};
