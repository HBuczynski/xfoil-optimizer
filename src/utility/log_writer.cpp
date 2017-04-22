#include <iostream>
#include <thread>

#include "time_manager.h"
#include "log_writer.h"

LogWriter *LogWriter::pInstance_ = nullptr;
std::mutex LogWriter::mutex_;

LogWriter& LogWriter::getInstance()
{
	if (!pInstance_)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (!pInstance_)
			pInstance_ = new LogWriter;
	}

	return *pInstance_;
}

LogWriter::LogWriter()
{

}

LogWriter::~LogWriter()
{
    destroy();
}

bool LogWriter::initialize(std::string directoryName)
{
    std::string filenameLog = directoryName + "/log_" + TimeManager::getStringDateTime() + ".txt";

    fileLog_.open(filenameLog.c_str());
    if (fileLog_.fail())
    {
        std::cout << "Error: LogWriter::initialize failed create log file. Exiting." << std::endl;
        return false;
    }

    isFileOpened_ = true;
    fileLog_.precision(5);
    return true;
}

void LogWriter::destroy()
{
    isFileOpened_ = false;
    fileLog_.close();
}


void LogWriter::addInformationMessage(std::string message)
{
    std::string messageFull = TimeManager::getStringTime();
    messageFull += " -> ";
    messageFull +=TimeManager::getStringTimeSinceStart();
    messageFull += "ms --> ";
    messageFull += "Info: ";
    messageFull += message;

    if (doWriteToConsole_)
    {
        std::cout << messageFull << std::endl;
    }

    if (isFileOpened_)
    {
        fileLog_ << messageFull << std::endl;
        fileLog_.flush();
    }

}


void LogWriter::addInformationMessage(const char *message)
{
    std::string messageFull = TimeManager::getStringTime();
    messageFull += " -> ";
    messageFull += TimeManager::getStringTimeSinceStart();
    messageFull += "ms --> ";
    messageFull += "Info: ";
    messageFull += message;

    if (doWriteToConsole_)
    {
        std::cout << messageFull << std::endl;
    }

    if (isFileOpened_)
    {
        fileLog_ << messageFull << std::endl;
        fileLog_.flush();
    }

}

void addErrorMessage(const std::string &message)
{
	addErrorMessage(message.c_str());
}

void LogWriter::addErrorMessage(const char *message)
{
    std::string messageFull = TimeManager::getStringTime();
    messageFull += " -> ";
    messageFull += TimeManager::getStringTimeSinceStart();
    messageFull += "ms --> ";
    messageFull += "Error: ";
    messageFull += message;

    if (doWriteToConsole_)
    {
        std::cout << messageFull << std::endl;
    }

    if (isFileOpened_)
    {
        fileLog_ << messageFull << std::endl;
        fileLog_.flush();
    }

}

void LogWriter::addWarningMessage(const char *message)
{
    std::string messageFull = TimeManager::getStringTime();
    messageFull += " -> ";
    messageFull += TimeManager::getStringTimeSinceStart();
    messageFull += "ms --> ";
    messageFull += "Warning: ";
    messageFull += message;

    if (doWriteToConsole_)
    {
        std::cout << messageFull << std::endl;
    }

    if (isFileOpened_)
    {
        fileLog_ << messageFull << std::endl;
        fileLog_.flush();
    }

}

void LogWriter::write(char * message)
{

    if (isFileOpened_)
    {
        fileLog_ << message << std::endl;
        fileLog_.flush();
    }

}
