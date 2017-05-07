#pragma once

#include <string>

#include "tiny_xml/tinystr.h"
#include "tiny_xml/tinyxml.h"
#include "log_writer.h"

class ConfigurationReader
{
public:
	ConfigurationReader();
	~ConfigurationReader();

	bool initialize();

private:
    void saveToFile(const char * fileName);
    bool loadFromFile(const char* fileName);
    void parametersInitialization();
    void addBranchToXML(TiXmlElement *root,std::string parentName, std::string childName);
    void loadApplicationParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot);

private:
    LogWriter *logger_;
};
