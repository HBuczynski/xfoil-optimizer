#include "model/model.h"
#include "utility/configuration_reader.h"
#include <QDebug>

Model::Model()
{
    initializeConfigurationReader();
    initializeLogger();
}

Model::~Model()
{

}

void Model::getTargetProfileValues(AviationProfileParameters data)
{
    targetProfileData_  = data;
}

void Model::getBaseProfileValues(AviationProfileParameters data)
{
    baseProfileData_ = data;
}

void Model::initializeLogger()
{
    logger_ = &LogWriter::getInstance();
}

void Model::initializeConfigurationReader()
{
    configReader_.initialize();
}
