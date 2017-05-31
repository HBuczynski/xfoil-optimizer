#pragma once
#include <vector>

#include "optimizer/airfoil_optimizer.h"
#include "xfoil/simulation.h"
#include "optimizer/genetic/genome.h"



//!  Class implementing genetic algorithm for optimization
/*!
  A more elaborate class description. [TODO]
*/

class GeneticOptimizer : public AirfoilOptimizer
{

public:
    enum GAState;

    GeneticOptimizer(): state_(NotInitialized)
    {

    }

    void Initialize();

    GAState GetState() const
    {
        return state_;
    }

    enum GAState
    {
        NotInitialized,
        SimulationInProgress,
        GenerationComplete,
        OptimizationCompleteTargetReached,
        OptimizationCompleteFinalGeneration
    };

    virtual void AddBaseGeometry(Geometry &geom)
    {

    }

    virtual void OptimizeStep()
    {

    }

    virtual Geometry const GetTopGeometry(int place)
    {
        //TODO//
        return baseGeometry_;
    }

    virtual double const GetProgress()
    {
        return 0.0;
    }

private:
    //Members//
    GAState state_;
    Geometry baseGeometry_;

    std::vector<Genome> population_;
    std::vector<Genome> elites_;
};
