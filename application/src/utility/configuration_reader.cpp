#include "configuration_reader.h"
#include "utility/utility.h"
#include "config.h"

#include <QDebug>

#if defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)

    #include <windows.h>
    std::string getUserName()
    {
        WCHAR result[MAX_PATH];
        std::wstring lol(result, GetModuleFileName(NULL, result, MAX_PATH));
        std::string str(lol.begin(), lol.end());
        str = str.substr(0, str.find_last_of("\\"));

        return str;
    }
    const static std::string separator("\\");
    const std::string ConfigurationReader::projectPath_ = getUserName()+"\\XFOIL_Optimizer\\";

#else

    #include <limits.h>
    #include <unistd.h>

    std::string getUserName()
    {
      char result[ PATH_MAX ];
      ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
      return std::string( result, (count > 0) ? count : 0 );
    }

    static const std::string separator("/");
    std::string ConfigurationReader::projectPath_ = getUserName() + "/XFOIL_Optimizer/";
#endif

const std::string ConfigurationReader::folderConfigName_ = "Config";
const std::string ConfigurationReader::fileConfigName_ = "XfoilParameters.xml";

ConfigurationReader::ConfigurationReader()
{

}

ConfigurationReader::~ConfigurationReader()
{

}

bool ConfigurationReader::initialize()
{
    qDebug() << projectPath_.c_str();
    if(!initializeDirectories())
    {
        std::cout << "Error: Basic directory wasn't created. Exiting." << std::endl;
        return false;
    }

    if(!initializeLogger())
    {
        std::cout << "Error: Logger wasn't initialized. Exiting." << std::endl;
        return false;
    }

    fileParametersPath_ = projectPath_ + ConfigurationReader::folderConfigName_ + separator + ConfigurationReader::fileConfigName_;

    if (loadFromFile(fileParametersPath_.c_str()))
    {
        logger_->addInformationMessage("ConfigurationReader:: parameters were loaded with success from file.");
        return true;
    }
    else
    {
        saveToFile(fileParametersPath_.c_str());
        if (loadFromFile(fileParametersPath_.c_str()))
        {
            logger_->addInformationMessage("ConfigurationReader:: parameters were loaded with success from file.");
            return true;
        }
        else
        {
            logger_->addErrorMessage("ConfigurationReader::failed to open xml file.");
            return false;
        }
    }
}

std::string ConfigurationReader::getProjectPath()
{
    return projectPath_;
}

ApplicationParameters ConfigurationReader::getApplicationParameters()
{
    return applicationParameters_;
}

OptimizationParameters ConfigurationReader::getOptimizerParameters()
{
    return optimizationParameters_;
}

bool ConfigurationReader::initializeDirectories()
{
   return utility::createDirectoryRecursively(projectPath_ + folderConfigName_);
}

bool ConfigurationReader::initializeLogger()
{
    std::string directoryLogger = projectPath_ + "Logger";
    bool isSuccess = utility::createDirectoryRecursively(directoryLogger);

    logger_ = &LogWriter::getInstance();

    return isSuccess && logger_->initialize(directoryLogger);
}

void ConfigurationReader::saveToFile(const char *fileName)
{
    initializeOptParameters();
    initializeAppParameters();

    TiXmlDocument document;
    TiXmlDeclaration *fileDeclaration = new TiXmlDeclaration("1.0", "", "");

    //add first paragraph to the file
    document.LinkEndChild(fileDeclaration);

    //first root of the xml document
    TiXmlElement *root = new TiXmlElement("Xfoil_Optimizer");
    document.LinkEndChild(root);

    TiXmlComment *comment = new TiXmlComment();
    comment->SetValue("Settings for Xfoil Optimizer");
    root->LinkEndChild(comment);

    addBranchToXML(root, "ApplicationParameters", "Param", applicationParameters_);
    addBranchToXML(root, "OptimizerParameters", "Param", optimizationParameters_);

    document.SaveFile(fileName);
}

void ConfigurationReader::initializeAppParameters()
{
    applicationParameters_["Config"] = "lolo";
}

void ConfigurationReader::initializeOptParameters()
{
    optimizationParameters_["Cl"] = 0.23;
}

bool ConfigurationReader::loadFromFile(const char *fileName)
{
    TiXmlDocument parametersFile(fileName);

    if (!parametersFile.LoadFile())
    {
        return false;
    }

    TiXmlHandle handleParametersFile(&parametersFile);
    TiXmlElement* pointerToElement;
    TiXmlHandle hRoot(0);

    //set pointer to first element - name
    pointerToElement = handleParametersFile.FirstChildElement().Element();

    if (!pointerToElement)
    {
        logger_->addErrorMessage("ConfigurationReader::failed to set pointer to first element in xml file.");
        return false;
    }

    hRoot = TiXmlHandle(pointerToElement);

    loadApplicationParameters(pointerToElement, hRoot);
    loadOptimizerParameters(pointerToElement, hRoot);

    return true;
}

void ConfigurationReader::addBranchToXML(TiXmlElement *root, std::string parentName, std::string childName, ApplicationParameters container)
{
    ApplicationParameters::iterator containerIter;

    TiXmlElement *parent = new TiXmlElement(parentName.c_str());
    root->LinkEndChild(parent);

    TiXmlElement *child;

    for (containerIter = container.begin(); containerIter != container.end(); containerIter++)
    {
        const std::string &key = (*containerIter).first;
        const std::string &value = (*containerIter).second;

        child = new TiXmlElement(childName.c_str());
        parent->LinkEndChild(child);
        child->SetAttribute(key.c_str(), value.c_str());
    }
}

void ConfigurationReader::addBranchToXML(TiXmlElement *root, std::string parentName, std::string childName, OptimizationParameters container)
{
    OptimizationParameters::iterator containerIter;

    TiXmlElement *parent = new TiXmlElement(parentName.c_str());
    root->LinkEndChild(parent);

    TiXmlElement *child;

    for (containerIter = container.begin(); containerIter != container.end(); containerIter++)
    {
        const std::string &key = (*containerIter).first;
        const double &value = (*containerIter).second;

        child = new TiXmlElement(childName.c_str());
        parent->LinkEndChild(child);
        child->SetDoubleAttribute(key.c_str(), value);
    }
}

void ConfigurationReader::loadApplicationParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot)
{
    pointerToElement = hRoot.FirstChild("ApplicationParameters").FirstChild().Element();

    for (pointerToElement; pointerToElement; pointerToElement = pointerToElement->NextSiblingElement())
    {
        pointerToElement->QueryStringAttribute("Config", &applicationParameters_["Config"]);
    }
}

void ConfigurationReader::loadOptimizerParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot)
{
    pointerToElement = hRoot.FirstChild("OptimizerParameters").FirstChild().Element();

    for (pointerToElement; pointerToElement; pointerToElement = pointerToElement->NextSiblingElement())
    {
        pointerToElement->QueryDoubleAttribute("Cl", &optimizationParameters_["Cl"]);
    }
}


