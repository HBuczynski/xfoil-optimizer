#pragma once
#include <vector>
#include <algorithm>
#include <vector>
#include <QObject>
#include "optimizer/airfoil_optimizer.h"
#include "xfoil/simulation.h"
#include "optimizer/genetic/genome.h"
#include "optimizer/genetic/genome_scrambler.h"
#include "utility/config.h"
#include "model/profile_parameters.h"

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
        Initialized,
        SimulationInProgress,
        GenerationComplete,
        OptimizationCompleteTargetReached,
        OptimizationCompleteFinalGeneration
    };

    GeneticOptimizer(Config::SimulationParams &params, Config::OptimizerParams &optParams);

    ~GeneticOptimizer();

    virtual void initialize(Geometry &geom);
    void runGeneticAlgorithm();
    GAState getState();

    virtual void optimizeStep();
    virtual Geometry const getTopGeometry();
    virtual double const getProgress();
    AviationProfileParameters calculateBasicProfile(std::string path);

    std::vector<double> getVectorX();
    std::vector<double> getVectorY();

    bool isRunning();
public Q_SLOTS:
    virtual void simulationBatchComplete();
    void requestStop();

Q_SIGNALS:
    void optimizationFinished();
    void newGenerationGenerated();
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
    std::vector<double> vectorX_;
    std::vector<double> vectorY_;

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
