#include "model/model.h"
#include "utility/configuration_reader.h"
#include "optimizer/genetic/genetic.h"
#include <QDebug>

Model::Model()
{
    initializeConfigurationReader();
    initializeLogger();
    initializeGeneticAlgorithm();
}

Model::~Model()
{
    delete geneticOptimizer_;
}

void Model::getTargetProfileValues(AviationProfileParameters data)
{
    targetProfileData_  = data;
}

void Model::calculateBaseProfileParameters(std::string path)
{

#if defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)
    std::string separator = "\\\\";
#else
    std::string separator ="/";
#endif

    while(path.find('/') != std::string::npos)
        path.replace(path.find('/'),1, separator.c_str());
    emit setBasicProfileParameters(geneticOptimizer_->calculateBasicProfile(path));
    emit updateBaseChart(geneticOptimizer_->getVectorX(), geneticOptimizer_->getVectorY());
}

void Model::stopSimulation()
{
    qDebug() << "stop";
}

void Model::startSimulation()
{
    qDebug() << "start simulation";
}

void Model::initializeLogger()
{
    logger_ = &LogWriter::getInstance();
}

void Model::initializeConfigurationReader()
{
    configReader_.initialize();

    applicationParameters_ = configReader_.getApplicationParameters();
    simulationParameters_ = configReader_.getSimulatorParameters();
    simulationParameters_.viscousEnable = false;
    optimizerParameres_ = configReader_.getOptimizerParameters();
    projectPath_ = configReader_.getProjectPath();
}

void Model::initializeGeneticAlgorithm()
{
    geneticOptimizer_ = new GeneticOptimizer(simulationParameters_, optimizerParameres_);
}
