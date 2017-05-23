#include "xfoil/simulation.h"

#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
bool SimulationHandler::FileExists(std::string filename)
{
    ifstream infile(filename);
    return infile.good();
}

void SimulationHandler::ReadResults()
{
    if(!FileExists(InstantiateFilename("polar.txt")))
        return;
}
std::string SimulationHandler::InstantiateFilename(std::string filename)
{
    std::string result;
    std::string::size_type idx = filename.find_last_of('.');
    if(idx != std::string::npos)
    {
        //Found externsion can add number
        result = filename.substr(0,idx);
        result += std::to_string(id_) + filename.substr(idx);
    }
    else
    {
        result = filename + std::to_string(id_);
    }
    std::cout<< result<<std::endl;
    return result;
}
