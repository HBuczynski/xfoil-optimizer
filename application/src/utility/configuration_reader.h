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
    ApplicationParameters getApplicationParameters();
    OptimizerParameters getOptimizerParameters();

private:
    bool initializeDirectories();
    bool initializeLogger();

    void saveToFile(const char * fileName);
    bool loadFromFile(const char* fileName);

    void loadApplicationParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot);
    void loadOptimizerParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot);

    void addBranchToXML(TiXmlElement *root,std::string parentName, std::string childName, ApplicationParameters map);
    void addBranchToXML(TiXmlElement *root,std::string parentName, std::string childName, OptimizerParameters map);

    void initializeAppParameters();
    void initializeOptParameters();

private:
    LogWriter *logger_;

    ApplicationParameters applicationParameters_;
    OptimizerParameters optimizationParameters_;

    static const std::string projectPath_;
    static const std::string folderConfigName_;
    static const std::string fileConfigName_;
    std::string fileParametersPath_;
};
