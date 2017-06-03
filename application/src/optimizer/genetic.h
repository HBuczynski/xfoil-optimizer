#pragma once
#include <vector>

#include "optimizer/airfoil_optimizer.h"
#include "optimizer/genetic_datatypes.h"
#include "xfoil/simulation.h"
#include "optimizer/geometry.h"



//!  Class implementing genetic algorithm for optimization
/*!
  A more elaborate class description. [TODO]
*/

class GeneticOptimizer : public AirfoilOptimizer
{

public:
    enum GAState
    {
        NotInitialized,
        SimulationInProgress,
        GenerationComplete,
        OptimizationCompleteTargetReached,
        OptimizationCompleteFinalGeneration
    };
    GeneticOptimizer():
        state_(NotInitialized)
    {

    }

    void Initialize()
    {

    }

    GAState GetState() const
    {
        return state_;
    }



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

    class Genome
    {
    private:
        Geometry currentGeom_;
    };
    class GenomeScrambler //This might need rethinking - maybe move to genome as it is genome specific...
    {
    public:
        virtual void Mutate(Genome &genome) = 0;
        virtual Genome Crossover(const Genome &g1, const Genome &g2) = 0;
    };
    class DudScrambler: public GenomeScrambler
    {
    public:
        virtual void Mutate(Genome &genome) override
        {

        }
       virtual Genome Crossover(const Genome &g1, const Genome &g2) override
       {
            return Genome();
       }
    };

    class FitnessCalculator
    {

    };
    //Members//
    GAState state_;
    Geometry baseGeometry_;
    std::vector<Genome> population_;
    std::vector<Genome> elites_;
};
