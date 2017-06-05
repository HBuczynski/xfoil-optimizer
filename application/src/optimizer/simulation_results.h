#pragma once
#include <vector>

/**
*	@file simulation_results.h
*	@brief Class containing simulation results from xfoil
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class containing simulation results from xfoil
/*!
  This class calculate airfoil's parameters based on the outputs from xfoil simulation.
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

    struct PolarPoint
    {
        double alfa;
        double param;
    };

    SimResults::PolarPoint CalcMaxCl() const;
    SimResults::PolarPoint CalcMinCd() const;
    SimResults::PolarPoint CalcMaxGlideRatio() const;
    double CalcAvgTorque() const;
    std::vector<ResultEntry>::size_type  GetPolarPointCount() const
    {
        return results_.size();
    }
    bool IsCalculated() const
    {
        return calculated_;
    }

private:
    std::vector<ResultEntry> results_;
    bool calculated_;
};
