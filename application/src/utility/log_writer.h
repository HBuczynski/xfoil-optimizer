#pragma once

#include <fstream>
#include <string>
#include <mutex>

/**
*	@file log_writer.h
*	@brief File conists logger class. Logger is implemented as singleton.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class containing methods add information about current state of application.
/*!
    Log writer provides to show the information on the console window and save it to the logger file. User is able to choose
    kind of message which he wants to show, i.e. information, warning or error. This class is essential for supply the data to behavior
    analysis of the program.
*/
class LogWriter
{

public:
    ~LogWriter();
	
    static LogWriter& getInstance();

	bool initialize(std::string directoryName);
    void destroy();

    void addInformationMessage(std::string message);
    void addInformationMessage(const char *message);

	void addErrorMessage(const std::string &message);
    void addErrorMessage(const char *message);

    void addWarningMessage(const char *message);
    void write(const char * message);

private:
	LogWriter();
	LogWriter(const LogWriter&) = delete;

	static LogWriter *pInstance_;

	std::ofstream fileLog_;
    bool isFileOpened_;
	bool doWriteToConsole_;

	static std::mutex mutex_;
};

