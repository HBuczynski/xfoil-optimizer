#include "configuration_reader.h"

ConfigurationReader::ConfigurationReader()
{

}

ConfigurationReader::~ConfigurationReader()
{

}

bool ConfigurationReader::initialize()
{
    logger_ = &LogWriter::getInstance();

    return true;
}

void ConfigurationReader::saveToFile(const char *fileName)
{

}

bool ConfigurationReader::loadFromFile(const char *fileName)
{
    return true;
}

void ConfigurationReader::parametersInitialization()
{

}

void ConfigurationReader::addBranchToXML(TiXmlElement *root, std::string parentName, std::string childName)
{

}

void ConfigurationReader::loadApplicationParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot)
{

}
