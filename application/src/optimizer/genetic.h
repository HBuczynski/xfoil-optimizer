#pragma once
#include <vector>

#include "optimizer/airfoil_optimizer.h"
#include "optimizer/genetic_datatypes.h"
#include "xfoil/simulation.h"




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

private:
    class Genome
    {

    };
    class GenomeScrambler //This might need retinking - maybe move to genome as it is genome specific...
    {
    public:
        virtual void Mutate(Genome &genome) = 0;
        virtual Genome Crossover(const Genome &g1, const Genome &g2) = 0;
    };
    class DudScrambler: public GenomeScrambler
    {
    public:
        virtual void Mutate(Genome const &genome) override
        {

        }
       virtual Genome Crossover(const Genome &g1, const Genome &g2) override
       {
            return Genome();
       }
    };
};
