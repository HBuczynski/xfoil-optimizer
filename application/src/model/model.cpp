#include "model/model.h"

#include <QDebug>

Model::Model()
{
    initializeLogger();
    initializeConfigurationReader();
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

}
