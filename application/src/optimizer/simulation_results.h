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

    SimResults::PolarPoint calcMaxCl() const;
    SimResults::PolarPoint calcMinCd() const;
    SimResults::PolarPoint calcMaxGlideRatio() const;
    double calcAvgTorque() const;
    std::vector<ResultEntry>::size_type  getPolarPointCount() const;
    bool isCalculated() const;

private:
    std::vector<ResultEntry> results_;
    bool calculated_;
};
