#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
//#include <cstdio>

#include "xfoil/simulation_results.h"
//#include "optimizer/geometry.h"
#include "xfoil/simulation_proxy.h"
#include "xfoil/qsimulation.h"
#include "utility/utility.h"
#include "utility/config.h"
#include <thread>
#include <queue>
#include <mutex>


//!  Class controlling execution single simulation tool using proxy interface
/*!
  Controls single instance of xfoil optimizer
*/
class SimulationHandler
{
    friend class SimulationHandler_tests;
public:
    enum Status
    {
        Idle,
        Running,
        Finished,
        Error,
        NotExisting
    };

    SimulationHandler(Geometry &geom):
        geometry_(geom),
        id_(++id_total),
        results_(nullptr),
        status_(Idle)
    {
        proxy_ = new QSimulationProxy();
        SaveGeometry();
    }
    ~SimulationHandler()
    {
        //Tidy up//
        DeleteGeometry();
        if(status_ != Idle)
            DeleteResults();
        if(proxy_->PollStatus() != QSimulationProxy::NotRunning)
            proxy_->Terminate();

        delete proxy_;

        if(results_ != nullptr)
            delete results_;
    }
    static Geometry GetNACAAirfoil(std::string code)
    {

        //Validate code//
        if(code.length() > 4)
            throw std::invalid_argument("Code invalid");
        else if(!std::all_of(code.begin(), code.end(), ::isdigit))
            throw std::invalid_argument("Code invalid");
        QSimulationProxy tmpproxy;
        tmpproxy.AddCommand("NACA 0012");
        tmpproxy.AddCommand("SAVE NACA0012.dat");
        tmpproxy.AddCommand("\r\n");
        tmpproxy.Run();
        tmpproxy.Terminate();
        std::string filepath = tmpproxy.GetExePath() + "/NACA0012.dat";
        Geometry retGeom(filepath);
        utility::removeFile(filepath);

        return retGeom;
    }
    void Run();
    Status PollStatus();
private:
    void ReadResults();
    void SaveGeometry();
    void DeleteGeometry();
    void DeleteResults();
    std::string InstantiateFilename(std::string filename);
    const int id_;
    SimulationProxy *proxy_;
    Geometry geometry_;
    SimResults *results_;
    Status status_;
    static unsigned int id_total;
};


//!  Class controlling execution of external simulation tools
/*!
  Controls multiple instances of xfoil optimizer running in parallel
  Runs a thread that polls and initiates all xfoil proxy instances
  Has an internal queue for requests
*/
class SimulationScheduler
{
public:
    SimulationScheduler(Config::Optimization::SimulationParams &params):
        parallelInstances_(params.parallelSimulations)
    {
        //Initialize handler state array//
        handlerStatus_ = new SimulationHandler::Status[parallelInstances_];
        for(int i =0; i < parallelInstances_; ++i)
        {
            handlerStatus_[i] = SimulationHandler::NotExisting;
        }
        //Initailize worker thread//
        workerEnable_ = true;
        workerThread_ = new std::thread (&SimulationScheduler::ConsumeTask, this);


    }
    ~SimulationScheduler()
    {
        //Terminate worker thread//
        workerEnable_ = false;
        workerThread_->join();
        delete workerThread_;
        delete[] handlerStatus_;
    }

    struct Task
    {
        Task(Geometry * geom):
            geometry(geom),
            handlerAssigned(-1)
        {

        }
        Geometry * geometry;
        int handlerAssigned = -1;
    };

private:
    void ConsumeTask();
    const int parallelInstances_;
    std::vector<Geometry*> tasks;
    std::queue<Task*> taskQueue_;
    SimulationHandler::Status *handlerStatus_;
    std::mutex queueMutex_;
    std::thread *workerThread_;
    bool workerEnable_;


};
