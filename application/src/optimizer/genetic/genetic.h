#pragma once
#include <vector>

#include "optimizer/airfoil_optimizer.h"
#include "xfoil/simulation.h"
#include "optimizer/genetic/genome.h"
#include "optimizer/genetic/genome_scrambler.h"
#include "utility/config.h"



//!  Class implementing genetic algorithm for optimization
/*!
  A more elaborate class description. [TODO]
*/

class GeneticOptimizer : public AirfoilOptimizer
{

public:
    enum GAState;

    GeneticOptimizer():
                                                        state_(GAState::NotInitialized),
                                                        totalFintess(0),
                                                        maxCoefficientValue_(3),
                                                        populationCount_(20),
                                                        elitesCount_(3),
                                                        continueOptimization_(true),
                                                        iterationNumber_(20),
                                                        simulationScheduler_(nullptr),
                                                        fitnessModel_(nullptr)
    {

    }

    ~GeneticOptimizer();

    void initialize(Config::SimulationParams &params, Config::OptimizerParams::Fitness &fitness);
    void runGeneticAlgorithm();
    GAState GetState();

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
    void generateInitialPopulation();
    void addGenomeToElite(Genome *genome);
    void addGenomeToPopulation(Genome *genome);
    void createPopulationAfterReproduction();
    bool checkGenomeFitness(Genome *genome);
    void calculateFitness();

    Genome *rouletteWheelSelection();
    AirfoilCoefficients generateRandomCoefficients();

private:

    //Members//
    GAState state_;
    DudScrambler scrambler_;
    SimulationScheduler *simulationScheduler_;
    FitnessModel *fitnessModel_;
    Geometry baseGeometry_;
    Config::SimulationParams simulationParams_;
    Config::OptimizerParams::Fitness fitnessParams_;


    bool continueOptimization_;
    std::vector<Genome*> population_;
    std::vector<Genome*> elites_;
    std::vector<Genome*> tempPopulation;
    double totalFintess;

    const int populationCount_;
    const int elitesCount_;
    const int maxCoefficientValue_;
    const int iterationNumber_;
};
