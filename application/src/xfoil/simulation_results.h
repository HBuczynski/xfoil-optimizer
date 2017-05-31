#pragma once
#include <vector>
//!  Class containing simulation results from xfoil
/*!
  A more elaborate class description. [TODO]
*/
class SimResults
{
    friend class SimulationHandler;
public:
    SimResults():
        calculated_(false)
    {}
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

    double CalcMaxCl() const;
    double CalcMinCd() const;
    double CalcMaxGlideRatio() const;
    double CalcAvgTorque() const;
    std::vector<ResultEntry>::size_type  GetPolarPointCount() const
    {
        return results.size();
    }
    bool IsCalculated() const
    {
        return calculated_;
    }

private:
    std::vector<ResultEntry> results;
    bool calculated_;
};
