#pragma once

#include <string>

#include "tiny_xml/tinystr.h"
#include "tiny_xml/tinyxml.h"
#include "log_writer.h"
#include "config.h"

/**
*	@file configuration_reader.h
*	@brief Class containing methods to generate and load parameters from xml file.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class containing methods to generate and load parameters from xml file.
/*!
  This class uses TinyXml library to write and read data to xml files.
*/
class ConfigurationReader
{
public:
	ConfigurationReader();
	~ConfigurationReader();

	bool initialize();

    static std::string getProjectPath();
    static std::string getParameterFilePath();
    static std::string getSeparator();

    Config::ApplicationParams getApplicationParameters();
    Config::OptimizerParams getOptimizerParameters();
    Config::SimulationParams getSimulatorParameters();

private:
    bool initializeDirectories();
    //bool initializeLogger();

    void saveToFile(const char * fileName);
    bool loadFromFile(const char* fileName);

    void loadApplicationParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot);
    void loadOptimizerParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot);
    void loadSimulatorParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot);

    void addBranchToXML(TiXmlElement *root,std::string parentName, std::string childName, Parameters map);

    void initializeAppParameters();
    void initializeOptParameters();
    void initializeSimParameters();


private:
   //LogWriter *logger_;

    Parameters optimizationParameters_;
    Parameters applicationParameters_;
    Parameters simulaotorParameters_;

    static const std::string projectPath_;
    static const std::string folderConfigName_;
    static const std::string fileConfigName_;
    const static std::string separator;

    std::string fileParametersPath_;
};
