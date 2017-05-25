#pragma once

#include <string>

struct ExceptionHandler : public std::exception
{
    ExceptionHandler(const std::string &ex);
    ~ExceptionHandler();

    std::string e;
};

namespace utility
{
    bool createDirectoryRecursively(const std::string &directory);
    bool fileExists(std::string file);
    void removeFile(std::string file);
}

