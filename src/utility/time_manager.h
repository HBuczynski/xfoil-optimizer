#pragma once
#pragma warning(disable : 4996)			//TO DO: check error message on windows platform
										// error is connected with std::localtime function
#include <chrono>
#include <string>

class TimeManager
{

public:
    TimeManager();
    ~TimeManager();

    static int getTimeSinceStart();
    static std::string getStringTimeSinceStart();
    static std::string getStringTime();
    static std::string getStringDate();
    static std::string getStringDateTime();
    static std::string getBootDateTime();

private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> timeStart_;
    static const std::string bootTime_;
    static const unsigned int stringLength_ = 100;
};

