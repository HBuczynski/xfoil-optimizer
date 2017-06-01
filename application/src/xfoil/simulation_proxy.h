#pragma once
#include "optimizer/simulation_results.h"
#include "optimizer/geometry.h"
#include <string>

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
    virtual void AddCommand(std::string command) = 0;
    virtual void Run() = 0;
    virtual void Terminate() = 0;
    virtual Status PollStatus() = 0;
    virtual std::string const GetProgramOutput() = 0;
    virtual std::string const GetExePath() = 0;
    //virtual void Configure() = 0;
};
