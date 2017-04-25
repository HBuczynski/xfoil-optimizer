#pragma once

#include <string>

class ConfigurationReader
{
public:
	ConfigurationReader();
	~ConfigurationReader();

	bool initialize();
	std::string getFilePath();
};