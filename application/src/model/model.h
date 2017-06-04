#pragma once

#include <vector>
#include <QObject>

#include "utility/log_writer.h"
#include "utility/configuration_reader.h"
#include "utility/config.h"
#include "model/profile_parameters.h"
#include "optimizer/genetic/genetic.h"

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
    void setBasicProfileParameters(AviationProfileParameters data);

public slots:
    void getTargetProfileValues(AviationProfileParameters data);
    void calculateBaseProfileParameters(std::string path);
    void stopSimulation();

private:
	void initializeLogger();
    void initializeConfigurationReader();
    void initializeGeneticAlgorithm();

    AviationProfileParameters targetProfileData_;
    LogWriter *logger_;
    ConfigurationReader configReader_;
    GeneticOptimizer *geneticOptimizer_;

    std::string projectPath_;
    Config::ApplicationParams applicationParameters_;
    Config::SimulationParams simulationParameters_;
//    OptimizerParameters optimizerParameres_;
};
