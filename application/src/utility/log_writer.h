#pragma once

#include <fstream>
#include <string>
#include <mutex>

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

