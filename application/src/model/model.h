#pragma once

#include <vector>
#include <QObject>

#include "utility/log_writer.h"
#include "model/profile_parameters.h"

class Model : public QObject
{
    Q_OBJECT

public:
	Model();
	~Model();

signals:
    void updateChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void setFitnessParameters(AviationProfileParameters data);

public slots:
    void getTargetProfileValues(AviationProfileParameters data);
    void getBaseProfileValues(AviationProfileParameters data);

private:
	void initializeLogger();
    void initializeConfigurationReader();

    AviationProfileParameters baseProfileData_;
    AviationProfileParameters targetProfileData_;
    LogWriter *logger_;
};
