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
    SimulationHandler(Geometry &geom):
        geometry_(geom),
        id_(++id_total),
        results_(nullptr)
    {
        proxy_ = new QSimulationProxy();
        SaveGeometry();
    }
    ~SimulationHandler()
    {
        DeleteGeometry();
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
private:
    void ReadResults();
    void SaveGeometry();
    void DeleteGeometry();
    std::string InstantiateFilename(std::string filename);
    const int id_;
    SimulationProxy *proxy_;
    Geometry geometry_;
    SimResults *results_;
    static unsigned int id_total;
};


