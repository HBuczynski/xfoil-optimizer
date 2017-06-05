#pragma once
#include "optimizer/simulation_results.h"
#include "optimizer/geometry.h"
#include <string>

/**
*	@file simulation_proxy.h
*	@brief IO stream interface abstraction.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  IO stream interface abstraction
/*!
  Interface class for future use in different environments
*/
class SimulationProxy
{
public:
    enum Status
    {
        NotRunning,
        Running,
        Finished,
        Error
    };

    virtual ~SimulationProxy()
    {}
    virtual void addCommand(std::string command) = 0;
    virtual void run() = 0;
    virtual void terminate() = 0;
    virtual Status pollStatus() = 0;
    virtual std::string const getProgramOutput() = 0;
    virtual std::string const getExePath() = 0;
    //virtual void Configure() = 0;
};
