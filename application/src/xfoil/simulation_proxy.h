#pragma once
#include "xfoil/simulation_results.h"
#include "optimizer/geometry.h"


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
        NotConverged,
        Error
    };
    virtual void Run() = 0;
    virtual void Terminate() = 0;
    virtual Status const GetStatus() = 0;
    //virtual void Configure() = 0;
};
