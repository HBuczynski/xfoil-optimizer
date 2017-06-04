#pragma once
#include <vector>
#include <QObject>
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
    Q_OBJECT
public:
    enum GAState
    {
        NotInitialized,
        SimulationInProgress,
        GenerationComplete,
        OptimizationCompleteTargetReached,
        OptimizationCompleteFinalGeneration
    };

    GeneticOptimizer(Config::SimulationParams &params, Config::OptimizerParams &optParams);

    ~GeneticOptimizer();

    void initialize();
    void runGeneticAlgorithm();
    GAState getState();

    virtual void addBaseGeometry(Geometry &geom);
    virtual void optimizeStep();
    virtual Geometry const getTopGeometry(int place);
    virtual double const getProgress();

    bool isRunning();

public Q_SLOTS:
    virtual void simulationBatchComplete();
    void requestStop();

Q_SIGNALS:
    void optimizationFinished();

private:
    void generateInitialPopulation();
    void addGenomeToElite(Genome *genome);
    void addGenomeToPopulation(Genome *genome);
    void createPopulationAfterReproduction();
    bool checkGenomeFitness(Genome *genome);
    void calculateFitness();

    Genome *rouletteWheelSelection();

private:

    //Members//
    GAState state_;
    GenomeScrambler *scrambler_;
    SimulationScheduler *simulationScheduler_;
    FitnessModel *fitnessModel_;
    Geometry baseGeometry_;
    const Config::SimulationParams simulationParams_;
    const Config::OptimizerParams optParams_;


    bool continueOptimization_;
    std::vector<Genome*> population_;
    std::vector<Genome*> elites_;
    std::vector<Genome*> tempPopulation;
    double totalFintess;

    const int elitesCount_;
    const int maxCoefficientValue_;
    int currentIterationNumber_ = 0;
    bool simRunning_;
};
