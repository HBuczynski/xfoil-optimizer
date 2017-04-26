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
    const std::vector<double> dataX;
    const std::vector<double> dataY;

    updateChart(dataX, dataY);
}

void Model::initializeLogger()
{
    logger_ = &LogWriter::getInstance();
}

void Model::initializeConfigurationReader()
{

}
