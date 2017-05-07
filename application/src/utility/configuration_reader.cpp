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

    //string directoryConfig = directoryPath_ + folderConfig_;

    bool isSuccess;// = utility::createDirectoryRecursively(directoryConfig);

    //fileParametersPath_ = ConfigurationReader::directoryPath_ + ConfigurationReader::folderConfig_ + "/" + ConfigurationReader::fileConfigName_;

        if (!isSuccess)
        {
            logger_->addErrorMessage("ConfiguarationReader::initialize failed to create directory config structure. Exiting.");
            logger_->write("\n\n/// Initializing not succeded :( ///\n\n");
            return false;
        }

        if (loadFromFile(projectParameterstPath_.c_str()))
        {
            return true;
        }
        else
        {
            saveToFile(projectParameterstPath_.c_str());
            if (loadFromFile(projectParameterstPath_.c_str()))
            {
                return true;
            }
            else
            {
                logger_->addErrorMessage("ConfigurationReader::failed to open xml file.");
                return false;
            }
        }

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
    pointerToElement = hRoot.FirstChild("ApplicationParameters").FirstChild().Element();

    for (pointerToElement; pointerToElement; pointerToElement = pointerToElement->NextSiblingElement())
    {
//        pointerToElement->QueryStringAttribute("logSubdirectoryName", &applicationParameters_.logSubdirectoryName);
//        pointerToElement->QueryStringAttribute("configSubdirectoryName", &applicationParameters_.configurationSubdirectoryName);
//        pointerToElement->QueryStringAttribute("dataDirectoryName", &applicationParameters_.dataDirectoryName);
//        pointerToElement->QueryStringAttribute("fmsPagesSubdirectory", &applicationParameters_.fmsPagesSubdirectoryName);
//        pointerToElement->QueryStringAttribute("airportsSubdirectoryName", &applicationParameters_.airportsSubdirectoryName);
//        pointerToElement->QueryStringAttribute("lastDataSubdirectoryName", &applicationParameters_.lastDataSubdirectoryName);
    }
}
