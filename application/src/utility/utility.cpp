#include "utility/utility.h"
#include "log_writer.h"

#include <QDir>

ExceptionHandler::ExceptionHandler(const std::string &ex) : e(ex)
{

}

ExceptionHandler::~ExceptionHandler()
{

}

bool utility::createDirectoryRecursively(const std::string &directory)
{
    #if defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)
        static const std::string separators("\\");
    #else
        static const std::string separators("/");
    #endif

    LogWriter *logger = &LogWriter::getInstance();

    // If the specified directory name doesn't exist, do our thing
    bool directoryStatus = QDir().exists(directory.c_str());

    if (!directoryStatus) {
            // Recursively do it all again for the parent directory, if any
            std::size_t slashIndex = directory.find_last_of(separators);
            if (slashIndex != std::string::npos) {
                bool isSuccess = utility::createDirectoryRecursively(directory.substr(0, slashIndex));
                if (!isSuccess)
                {
                    logger->addErrorMessage("utility::createDirectoryRecursively could not create parent directory.");
                    return false;
                }
            }

            // Create the last directory on the path (the recursive calls will have taken
            // care of the parent directories by now)
            bool result = QDir().mkdir(directory.c_str());

            if (result == false) {
                logger->addErrorMessage("utility::createDirectoryRecursively could not create directory.");
                return false;
            }
            return true;
    }
    else { // Specified directory name already exists

            if(false)
            {
                logger->addErrorMessage("utility::createDirectoryRecursively "
                    "failed to create directory because a file with the same name exists.");
                return false;
            }
            return true;
    }
}
