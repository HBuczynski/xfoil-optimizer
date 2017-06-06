#pragma once
#include <vector>

/**
*	@file simulation_results.h
*	@brief Class containing simulation results from xfoil
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!
/*!
  This class calculate airfoil's parameters based on the outputs from xfoil simulation.
*/
/**
*	@struct SimResults::ResultEntry
*   \brief Class containing simulation results from xfoil
*   Structure for storing simulation results from xfoil panel optimizer
*   @var SimResults::ResultEntry::alfa
*   airfoil angle of attack for the calculation
*   @var SimResults::ResultEntry::cl
*   Lift coefficient
*   @var SimResults::ResultEntry:cd
*   Drag coefficient
*   @var SimResults::ResultEntry::cdp
*   Pressure coefficient
*   @var SimResults::ResultEntry::cm
*   Tirque coefficient
*   @var SimResults::ResultEntry::xtr_top
*   Top transition point
*   @var SimResults::ResultEntry::xtr_bottom
*   Bottom transition point
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
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
