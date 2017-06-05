#pragma once
#include <string>

/**
*	@file utility.h
*	@brief This header file consists exception handler. Moreover it provides utility namespace to make basic operation on files
*          and directories.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Exception Handler.
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

