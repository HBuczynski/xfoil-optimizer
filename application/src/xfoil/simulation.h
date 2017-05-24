#pragma once

#include <vector>
#include "xfoil/simulation_results.h"
#include "optimizer/geometry.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/qsimulation.h"

//!  Class controlling execution of external simulation tools
/*!
  Controls multiple instances of xfoil optimizer running in parallel
*/
class SimulationScheduler
{
public:
private:
	const int _parallelInstances = 4;
    std::vector<Geometry*> tasks;



};
//!  Class controlling execution single simulation tool using proxy interface
/*!
  Controls single instance of xfoil optimizer
*/
class SimulationHandler
{
public:
    SimulationHandler(int handler_id):
        id_(handler_id),
        results_(nullptr)
    {
        InstantiateFilename("lol.txt");
        InstantiateFilename("lol");
        proxy_ = new QSimulationProxy();

    }
    ~SimulationHandler()
    {
        if(proxy_->PollStatus() != QSimulationProxy::NotRunning)
            proxy_->Terminate();

        delete proxy_;

        if(results_ != nullptr)
            delete results_;
    }
    Geometry GetNACAAirfoil();
private:
    void ReadResults();
    bool FileExists(std::string filenames);
    void SaveGeometry();
    std::string InstantiateFilename(std::string filename);
    const int id_;
    SimulationProxy *proxy_;
    Geometry geometry_;
    SimResults *results_;
};


