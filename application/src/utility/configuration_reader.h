#pragma once

#include <string>

#include "tiny_xml/tinystr.h"
#include "tiny_xml/tinyxml.h"
#include "log_writer.h"
#include "config.h"


class ConfigurationReader
{
public:
	ConfigurationReader();
	~ConfigurationReader();

	bool initialize();

    static std::string getProjectPath();

    Config::ApplicationParams getApplicationParameters();
    Config::OptimizerParams getOptimizerParameters();
    Config::SimulationParams getSimulatorParameters();

private:
    bool initializeDirectories();
    bool initializeLogger();

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
    LogWriter *logger_;

    Parameters optimizationParameters_;
    Parameters applicationParameters_;
    Parameters simulaotorParameters_;

    static const std::string projectPath_;
    static const std::string folderConfigName_;
    static const std::string fileConfigName_;

    std::string fileParametersPath_;
};
