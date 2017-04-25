#include <ctime>
#include <iomanip>
#include <memory>

#include "time_manager.h"

using namespace std::chrono;

time_point<high_resolution_clock> TimeManager::timeStart_ = high_resolution_clock::now();

//String containing boot time for directories created on initialization
const std::string TimeManager::bootTime_ = TimeManager::getStringDateTime();

TimeManager::TimeManager()
{

}


TimeManager::~TimeManager()
{

}

int TimeManager::getTimeSinceStart()
{
    time_point<high_resolution_clock> timeCurrent = high_resolution_clock::now();
    duration<double> timeSinceStart = duration_cast<duration<double>>(timeCurrent - timeStart_);
    return (int)(timeSinceStart.count() * 1000);
}

std::string TimeManager::getStringTimeSinceStart()
{
    time_point<high_resolution_clock> timeCurrent = high_resolution_clock::now();
    duration<double> timeSinceStart = duration_cast<duration<double>>(timeCurrent - timeStart_);

    std::string  t = std::to_string((int)(timeSinceStart.count() * 1000));

    if (t.size() < 8)
        while (t.size() < 8)
            t.insert(0, " ");

    return t;
}

std::string TimeManager::getStringTime()
{
    std::unique_ptr<char> stringTime(new char[stringLength_]);
    std::time_t timeCurrent = std::time(nullptr);
    std::tm *timeLocal = std::localtime(&timeCurrent);
    std::strftime(stringTime.get(), stringLength_, "%H.%M.%S", timeLocal);
    std::string stringResult(stringTime.get());
    return stringResult;
}

std::string TimeManager::getStringDate()
{
    std::unique_ptr<char> stringDate(new char[stringLength_]);
    std::time_t timeCurrent = std::time(nullptr);
    std::tm *timeLocal = std::localtime(&timeCurrent);
    std::strftime(stringDate.get(), stringLength_, "%y.%m.%d", timeLocal);
    std::string stringResult(stringDate.get());
    return stringResult;
}

std::string TimeManager::getStringDateTime()
{
    std::unique_ptr<char> stringDateTime(new char[stringLength_]);
    std::time_t timeCurrent = std::time(nullptr);
    std::tm *timeLocal = std::localtime(&timeCurrent);
    std::strftime(stringDateTime.get(), stringLength_, "%y.%m.%d_%H.%M.%S", timeLocal);
    std::string stringResult(stringDateTime.get());
    return stringResult;
}

std::string TimeManager::getBootDateTime()
{
    return TimeManager::bootTime_;
}

