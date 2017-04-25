#pragma once

//!  Class containing simulation results from xfoil
/*!
  A more elaborate class description. [TODO]
*/
class SimResults
{
    friend class SimulationProxy;
public:
    double CalcMaxCl();
    double CalcMinCd();
private:
    int someresults;
};
