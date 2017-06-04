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

    qDebug() << path.c_str();

}

void Model::stopSimulation()
{
    qDebug() << "stop";
}

void Model::initializeLogger()
{
    logger_ = &LogWriter::getInstance();
}

void Model::initializeConfigurationReader()
{
    configReader_.initialize();

    //to do - do smt if initialize return false

    applicationParameters_ = configReader_.getApplicationParameters();
    //simulationParameters_ = configReader_.getSimulatorParameters();
//    optimizerParameres_ = configReader_.getOptimizerParameters();
    projectPath_ = configReader_.getProjectPath();
}

void Model::initializeGeneticAlgorithm()
{
   // geneticOptimizer_.initialize(simulationParameters_);
}
