#include "model/model.h"

Model::Model()
{
    initializeLogger();

    initializeConfigurationReader();
}

Model::~Model()
{

}

void Model::setProfileData(AviationProfileParameters &data)
{

}

void Model::updateChart(std::vector<double> dataX, std::vector<double> dataY)
{

}

void Model::initializeLogger()
{
    logger_ = &LogWriter::getInstance();
}

void Model::initializeConfigurationReader()
{

}
