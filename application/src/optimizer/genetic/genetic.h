#pragma once
#include <vector>
#include <QObject>
#include "optimizer/airfoil_optimizer.h"
#include "xfoil/simulation.h"
#include "optimizer/genetic/genome.h"
#include "optimizer/genetic/genome_scrambler.h"
#include "utility/config.h"

/**
*	@file genetic.h
*	@brief File consists header for genetic algorithm.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class contains implementation of the genetic algorithm
/*!
*  Genetic Optimizer provides necessary objects and methods to use genetic algorithm.
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

    GeneticOptimizer(Config::SimulationParams &params, Config::OptimizerParams::Fitness &fitness):
                                                        state_(GAState::NotInitialized),
                                                        totalFintess(0),
                                                        maxCoefficientValue_(3),
                                                        populationCount_(20),
                                                        elitesCount_(3),
                                                        continueOptimization_(true),
                                                        iterationLimit_(20),
                                                        simulationScheduler_(nullptr),
                                                        fitnessModel_(nullptr)
    {

        simulationParams_ = params;
        fitnessParams_ = fitness;
        //TO DO: constructor was changed
        simulationScheduler_ = new SimulationScheduler(simulationParams_);
        fitnessModel_ = new FitnessModel(fitnessParams_);
        QObject::connect(simulationScheduler_, SIGNAL(simulationFinished()), this, SLOT(simulationBatchComplete()));
    }

    ~GeneticOptimizer();

    void initialize();
    void runGeneticAlgorithm();
    GAState GetState();



    virtual void AddBaseGeometry(Geometry &geom)
    {

    }

    virtual void OptimizeStep();

    virtual Geometry const GetTopGeometry(int place)
    {
        //TODO//
        return baseGeometry_;
    }

    virtual double const GetProgress()
    {
        return 0.0;
    }
public Q_SLOTS:
    virtual void simulationBatchComplete();
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
    const int iterationLimit_;
    int currentIterationNumber_ = 0;
};
