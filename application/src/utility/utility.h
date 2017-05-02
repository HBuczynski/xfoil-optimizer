#pragma once

#include <string>

struct ApplicationParameters
{

};

struct ExceptionHandler : public std::exception
{
    ExceptionHandler(const std::string ex);
    ~ExceptionHandler();

    std::string e;
};

namespace utility
{
    bool createDirectoryRecursively(const std::string &directory);
}

