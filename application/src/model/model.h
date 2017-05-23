#pragma once

#include <vector>
#include <QObject>

#include "utility/log_writer.h"
#include "utility/configuration_reader.h"
#include "model/profile_parameters.h"

class Model : public QObject
{
    Q_OBJECT

public:
	Model();
	~Model();

signals:
    void updateBaseChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void updateOptimizedChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
    void updateGeneticChart(const std::vector<double> &dataX, const std::vector<double> &dataY);
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
    ConfigurationReader configReader_;
};
