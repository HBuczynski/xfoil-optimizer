#include "configuration_reader.h"
#include "utility/utility.h"
#include "config.h"

#include <QDebug>
#include <typeinfo>

#if defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)

    #include <windows.h>
    const static std::string separator("\\");
    std::string path = []()->std::string {
                                            WCHAR result[MAX_PATH];
                                            std::wstring lol(result, GetModuleFileName(NULL, result, MAX_PATH));
                                            std::string str(lol.begin(), lol.end());
                                            str = str.substr(0, str.find_last_of("\\"));

                                            return str;
                                        }();
    const std::string ConfigurationReader::projectPath_ = path +"\\XFOIL_Optimizer\\";

#else

    #include <limits.h>
    #include <unistd.h>

    static const std::string separator("/");
    std::string path = []()->std::string {
                                          char result[ PATH_MAX ];
                                          ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
                                          std::string str(result);
                                          str = str.substr(0, str.find_last_of("/"));
                                          return str;
                                         }();
    std::string  getUserName()
    {
        char username[LOGIN_NAME_MAX];
        getlogin_r(username, LOGIN_NAME_MAX);
        return std::string(username);
    }

    const std::string ConfigurationReader::projectPath_ = path + "/XFOIL_Optimizer/";
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
    //qDebug() << projectPath_.c_str();
    if(!initializeDirectories())
    {
        std::cout << "Error: Basic directory wasn't created. Exiting." << std::endl;
        return false;
    }
/*
    if(!initializeLogger())
    {
        std::cout << "Error: Logger wasn't initialized. Exiting." << std::endl;
        //return false;
    }
*/
    fileParametersPath_ = projectPath_ + ConfigurationReader::folderConfigName_ + separator + ConfigurationReader::fileConfigName_;

    if (loadFromFile(fileParametersPath_.c_str()))
    {
        //std::cout << "Error: Logger wasn't initialized. Exiting." << std::endl;
        //logger_->addInformationMessage("ConfigurationReader:: parameters were loaded with success from file.");
        return true;
    }
    else
    {
        saveToFile(fileParametersPath_.c_str());
        if (loadFromFile(fileParametersPath_.c_str()))
        {

            //logger_->addInformationMessage("ConfigurationReader:: parameters were loaded with success from file.");
            return true;
        }
        else
        {
            std::cout << "ConfigurationReader::failed to open xml file."<< std::endl;
            //logger_->addErrorMessage("ConfigurationReader::failed to open xml file.");
            return false;
        }
    }
}

std::string ConfigurationReader::getProjectPath()
{
    return projectPath_;
}
std::string ConfigurationReader::getParameterFilePath()
{
    return projectPath_ + folderConfigName_ + separator + fileConfigName_;
}

Config::ApplicationParams ConfigurationReader::getApplicationParameters()
{
    Config::ApplicationParams rparams;
    return rparams;
}

Config::OptimizerParams ConfigurationReader::getOptimizerParameters()
{
    Config::OptimizerParams rparams;
    rparams.fitness.optimizeStall = boost::get<std::string>(optimizationParameters_["optimizeStall"]) == "True";
    rparams.fitness.optimizeCl = boost::get<std::string>(optimizationParameters_["optimizeCl"]) == "True";
    rparams.fitness.optimizeCl = boost::get<std::string>(optimizationParameters_["optimizeCl"]) == "True";
    rparams.fitness.optimizeMoment = boost::get<std::string>(optimizationParameters_["optimizeMoment"]) == "True";
    rparams.fitness.optimizeGlide = boost::get<std::string>(optimizationParameters_["optimizeGlide"]) == "True";

    rparams.fitness.targetCd = boost::get<double>(optimizationParameters_["targetCd"]);
    rparams.fitness.targetCl = boost::get<double>(optimizationParameters_["targetCl"]);
    rparams.fitness.targetGlide = boost::get<double>(optimizationParameters_["targetGlide"]);
    rparams.fitness.targetMoment = boost::get<double>(optimizationParameters_["targetMoment"]);
    rparams.fitness.targetStallAlfa = boost::get<double>(optimizationParameters_["targetStalAlfa"]);
    rparams.fitness.weightCd = boost::get<double>(optimizationParameters_["weightCd"]);
    rparams.fitness.weightCl = boost::get<double>(optimizationParameters_["weightCl"]);
    rparams.fitness.weightGlide = boost::get<double>(optimizationParameters_["weightGlide"]);
    rparams.fitness.weightMoment = boost::get<double>(optimizationParameters_["weightMoment"]);
    rparams.fitness.weightStall = boost::get<double>(optimizationParameters_["weightStall"]);
    return rparams;
}
Config::SimulationParams ConfigurationReader::getSimulatorParameters()
{
    Config::SimulationParams rparams;
    rparams.iterationLimit = boost::get<int>(simulaotorParameters_["maxIterations"]);
    rparams.parallelSimulations = boost::get<int>(simulaotorParameters_["parallelTasks"]);
    rparams.reynoldsNo = boost::get<int>(simulaotorParameters_["viscousRe"]);
    //rparams.viscousEnable = boost::get<std::string>(simulaotorParameters_["viscousEnable"]) == "True";
    rparams.xfoilExecutablePath = boost::get<std::string>(simulaotorParameters_["xfoilPath"]);
    rparams.xfoilTimeout = boost::get<int>(simulaotorParameters_["xfoilTimeout"]);
    return rparams;
}


bool ConfigurationReader::initializeDirectories()
{
   return utility::createDirectoryRecursively(projectPath_ + folderConfigName_);
}
/*
bool ConfigurationReader::initializeLogger()
{
    std::string directoryLogger = projectPath_ + "Logger";
    bool isSuccess = utility::createDirectoryRecursively(directoryLogger);
    std::cout<<"Success??:"<<isSuccess<<std::endl;
    logger_ = &LogWriter::getInstance();
    return isSuccess && logger_->initialize(directoryLogger);
}
*/
void ConfigurationReader::saveToFile(const char *fileName)
{
    initializeOptParameters();
    initializeAppParameters();
    initializeSimParameters();

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
    addBranchToXML(root, "SimulatorParameters", "Param", simulaotorParameters_);

    document.SaveFile(fileName);
}

void ConfigurationReader::initializeAppParameters()
{
    applicationParameters_["Config"] = "lolo";
}

void ConfigurationReader::initializeOptParameters()
{
    Config::OptimizerParams dparams;
    //Fitness parameters//
    optimizationParameters_["optimizeStall"] = dparams.fitness.optimizeStall;
    optimizationParameters_["optimizeCl"] =dparams.fitness.optimizeCl;
    optimizationParameters_["optimizeCd"] =dparams.fitness.optimizeCd;
    optimizationParameters_["optimizeMoment"] =dparams.fitness.optimizeMoment;
    optimizationParameters_["optimizeGlide"] =dparams.fitness.optimizeGlide;
    optimizationParameters_["targetCd"] =dparams.fitness.targetCd;
    optimizationParameters_["targetCl"] =dparams.fitness.targetCl;
    optimizationParameters_["targetGlide"] =dparams.fitness.targetGlide;
    optimizationParameters_["targetMoment"] =dparams.fitness.targetMoment;
    optimizationParameters_["targetStall"] =dparams.fitness.targetStallAlfa;
    optimizationParameters_["weightCd"] =dparams.fitness.weightCd;
    optimizationParameters_["weightCl"] =dparams.fitness.weightCl;
    optimizationParameters_["weightGlide"] =dparams.fitness.weightGlide;
    optimizationParameters_["weightMoment"] =dparams.fitness.weightMoment;
    optimizationParameters_["weightStall"] =dparams.fitness.weightStall;
}

void ConfigurationReader::initializeSimParameters()
{
    Config::SimulationParams dparams;
    simulaotorParameters_["parallelTasks"] = dparams.parallelSimulations;
    simulaotorParameters_["xfoilPath"] = dparams.xfoilExecutablePath;
    simulaotorParameters_["maxIterations"] = dparams.iterationLimit;
    simulaotorParameters_["viscousRe"] = dparams.reynoldsNo;
    simulaotorParameters_["viscousEnable"] = dparams.viscousEnable==true ? "True" : "False";
    simulaotorParameters_["xfoilTimeout"] = dparams.xfoilTimeout;
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
        std::cout<<"ConfigurationReader::failed to set pointer to first element in xml file.\r\n";
        //logger_->addErrorMessage("ConfigurationReader::failed to set pointer to first element in xml file.");
        return false;
    }

    hRoot = TiXmlHandle(pointerToElement);

    loadApplicationParameters(pointerToElement, hRoot);
    loadOptimizerParameters(pointerToElement, hRoot);
    loadSimulatorParameters(pointerToElement, hRoot);

    return true;
}

void ConfigurationReader::addBranchToXML(TiXmlElement *root, std::string parentName, std::string childName, Parameters container)
{
    Parameters::iterator containerIter;

    TiXmlElement *parent = new TiXmlElement(parentName.c_str());
    root->LinkEndChild(parent);

    TiXmlElement *child;

    for (containerIter = container.begin(); containerIter != container.end(); containerIter++)
    {
        const std::string &key = (*containerIter).first;

        if(((*containerIter).second).type() == typeid(std::string))
        {
            const std::string &value =  boost::get<std::string>((*containerIter).second);

            child = new TiXmlElement(childName.c_str());
            parent->LinkEndChild(child);
            child->SetAttribute(key.c_str(), value.c_str());
        }
        else if (((*containerIter).second).type() == typeid(double))
        {
            const double &value =  boost::get<double>((*containerIter).second);

            child = new TiXmlElement(childName.c_str());
            parent->LinkEndChild(child);
            child->SetDoubleAttribute(key.c_str(), value);
        }
        else if (((*containerIter).second).type() == typeid(int))
        {
            const int &value =  boost::get<int>((*containerIter).second);

            child = new TiXmlElement(childName.c_str());
            parent->LinkEndChild(child);
            child->SetAttribute(key.c_str(), value);
        }
    }
}

void ConfigurationReader::loadApplicationParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot)
{
    pointerToElement = hRoot.FirstChild("ApplicationParameters").FirstChild().Element();

    std::string tempString;
    int tempInt;
    double tempDouble;

    for (pointerToElement; pointerToElement; pointerToElement = pointerToElement->NextSiblingElement())
    {
        pointerToElement->QueryStringAttribute("Config", &tempString);
            applicationParameters_["Config"] = tempString;
        pointerToElement->QueryIntAttribute("IntTest", &tempInt);
            applicationParameters_["IntTest"] = tempInt;
        pointerToElement->QueryDoubleAttribute("DoubleTest", &tempDouble);
            applicationParameters_["DoubleTest"] = tempDouble;
    }
}

void ConfigurationReader::loadOptimizerParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot)
{
    pointerToElement = hRoot.FirstChild("OptimizerParameters").FirstChild().Element();

    std::string tempString;
    int tempInt;
    double tempDouble;

    for (pointerToElement; pointerToElement; pointerToElement = pointerToElement->NextSiblingElement())
    {
        pointerToElement->QueryDoubleAttribute("optimizeStall", &tempDouble);
        optimizationParameters_["optimizeStall"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("optimizeCl", &tempDouble);
        optimizationParameters_["optimizeCl"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("optimizeCd", &tempDouble);
        optimizationParameters_["optimizeCd"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("optimizeMoment", &tempDouble);
        optimizationParameters_["optimizeMoment"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("optimizeGlide", &tempDouble);
        optimizationParameters_["optimizeGlide"] = tempDouble;

        pointerToElement->QueryDoubleAttribute("targetStall", &tempDouble);
        optimizationParameters_["targetStall"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("targetCl", &tempDouble);
        optimizationParameters_["targetCl"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("targetCd", &tempDouble);
        optimizationParameters_["targetCd"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("targetMoment", &tempDouble);
        optimizationParameters_["targetMoment"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("targetGlide", &tempDouble);
        optimizationParameters_["targetGlide"] = tempDouble;

        pointerToElement->QueryDoubleAttribute("weightStall", &tempDouble);
        optimizationParameters_["weightStall"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("weightCl", &tempDouble);
        optimizationParameters_["weightCl"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("weightCd", &tempDouble);
        optimizationParameters_["weightCd"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("weightMoment", &tempDouble);
        optimizationParameters_["weightMoment"] = tempDouble;
        pointerToElement->QueryDoubleAttribute("weightGlide", &tempDouble);
        optimizationParameters_["weightGlide"] = tempDouble;

    }
}

void ConfigurationReader::loadSimulatorParameters(TiXmlElement *pointerToElement, TiXmlHandle &hRoot)
{
    pointerToElement = hRoot.FirstChild("SimulatorParameters").FirstChild().Element();

    std::string tempString;
    int tempInt;
    double tempDouble;

    for (pointerToElement; pointerToElement; pointerToElement = pointerToElement->NextSiblingElement())
    {
        pointerToElement->QueryIntAttribute("parallelTasks", &tempInt);
            simulaotorParameters_["parallelTasks"] = tempInt;
        pointerToElement->QueryStringAttribute("xfoilPath", &tempString);
            simulaotorParameters_["xfoilPath"] = tempString;
        pointerToElement->QueryIntAttribute("viscousRe", &tempInt);
            simulaotorParameters_["viscousRe"] = tempInt;
        pointerToElement->QueryStringAttribute("viscousEnable", &tempString);
            simulaotorParameters_["viscousEnable"] = tempString;
        pointerToElement->QueryIntAttribute("xfoilTimeout", &tempInt);
            simulaotorParameters_["xfoilTimeout"] = tempInt;
    }
}


