#pragma once

#include <vector>
#include <QObject>

#include "utility/log_writer.h"
#include "model/profile_parameters.h"

//typedef const std::vector<double> std::vector<double> &;


class Model : public QObject
{
    Q_OBJECT

public:
	Model();
	~Model();

    void setProfileData(AviationProfileParameters &data);

signals:
    void updateChart(const std::vector<double> &dataX, const std::vector<double> &dataY);

private:
	void initializeLogger();
	void initializeConfigurationReader();

    AviationProfileParameters baseProfileData_;
    LogWriter *logger_;

};
