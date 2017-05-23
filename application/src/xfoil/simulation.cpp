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
    if(!FileExists("hlor"))
        return;
}
std::string SimulationHandler::InstantiateFilename(std::string filename)
{
    //if(fn.substr(fn.find_last_of(".") + 1) == "conf") {
    //  std::cout << "Yes..." << std::endl;
    //} else {
    //  std::cout << "No..." << std::endl;
    //}
    return "";
}
