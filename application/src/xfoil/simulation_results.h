#pragma once
#include <vector>
//!  Class containing simulation results from xfoil
/*!
  A more elaborate class description. [TODO]
*/
class SimResults
{
public:
    struct ResultEntry
    {
        float alfa;
        float cl;
        float cd;
        float cdp;
        float cm;
        float xtr_top;
        float xtr_bottom;
    };

    double CalcMaxCl();
    double CalcMinCd();
    double CalcMaxGlideRatio();
    double CalcAvgTorque();
private:
    std::vector<ResultEntry> results;
};
