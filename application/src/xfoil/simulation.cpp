#include "xfoil/simulation.h"

using std::ifstream;
unsigned int SimulationHandler::id_total = 0;
void SimulationHandler::ReadResults()
{
   // if(!utility::fileExistss(InstantiateFilename("polar.txt")))
   //     return;
    std::ifstream infile(proxy_->GetExePath() + "/" + InstantiateFilename("polar.txt"));
    if(infile.good())
    {
        infile.close();
    }
    else
        throw std::exception("Invalid data file");


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
    //std::cout<< result<<std::endl;
    return result;
}
void SimulationHandler::SaveGeometry()
{
    geometry_.Save(proxy_->GetExePath() + "/" + InstantiateFilename("geometry.dat"));
}

void SimulationHandler::DeleteGeometry()
{
    std::remove((proxy_->GetExePath() + "/" + InstantiateFilename("geometry.dat")).c_str());
}
