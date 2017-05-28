#include "xfoil/simulation.h"

using std::ifstream;
unsigned int SimulationHandler::id_total = 0;
void SimulationHandler::ReadResults()
{
    std::ifstream infile(proxy_->GetExePath() + "/" + InstantiateFilename("result.txt"));
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
    geometry_.Save((std::string)(proxy_->GetExePath() + "\\" + InstantiateFilename("geometry.dat")));
}

void SimulationHandler::DeleteGeometry()
{
   // std::cout<< "DELETE GEOM "<< InstantiateFilename("geometry.dat")<<std::endl;
    std::remove((proxy_->GetExePath() + "/" + InstantiateFilename("geometry.dat")).c_str());
}
void SimulationHandler::DeleteResults()
{
    //std::cout<< "DELETE RES "<<InstantiateFilename("result.dat")<<std::endl;
    std::remove((proxy_->GetExePath() + "/" + InstantiateFilename("result.txt")).c_str());
}
void SimulationHandler::Run()
{
    if(status_ != Idle)
        throw std::exception("Invaid state - simulation running?");
    //TODO various paths for different setup options//
    proxy_->AddCommand("PLOP");
    proxy_->AddCommand("G F");
    proxy_->AddCommand("\r\n");
    proxy_->AddCommand("LOAD " + InstantiateFilename("geometry.dat"));
    proxy_->AddCommand("OPER");
    proxy_->AddCommand("VISC 1e6");//Set viscous flow reynolds number
    proxy_->AddCommand("PACC");
    proxy_->AddCommand("");//do not save tmp
    proxy_->AddCommand("");//do not save polar
    proxy_->AddCommand("ASEQ -10.0 18.0 0.2");//Sample range with angle step
    proxy_->AddCommand("PACC");//Disable polar accumulation

    proxy_->AddCommand("PWRT 1");
    proxy_->AddCommand(InstantiateFilename("result.txt"));

    //proxy_->AddCommand("CPWR " + InstantiateFilename("result.txt"));
    proxy_->Run();
    status_ = Running;
    //Check if proxy really started - state error if it didnt//
    if(proxy_->PollStatus() == SimulationProxy::NotRunning)
        status_ = Error;//TODO add log message
    std::cout <<"Running";

}
SimulationHandler::Status SimulationHandler::PollStatus()
{
    if(status_ != Error && status_ != Finished)//Final states check
       {
        SimulationProxy::Status proxy_status = proxy_->PollStatus();
        switch(proxy_status)
        {
            case SimulationProxy::NotRunning:
                status_ = Idle;
            break;
            case SimulationProxy::Running://Verify timeout TODO//
                std::cout <<"...";
                status_ = Running;
            break;
            case SimulationProxy::Error:
                status_ = Error;
            break;
            case SimulationProxy::Finished:
                ReadResults();
                status_ = Finished;
            break;
        default:
            break;
        }
    }
    return status_;
}

