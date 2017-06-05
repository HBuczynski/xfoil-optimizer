#pragma once
#include <vector>
#include <algorithm>
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

    GeneticOptimizer(Config::SimulationParams &params, Config::OptimizerParams &optParams):
                                                        simRunning_(false),
                                                        state_(GAState::NotInitialized),
                                                        totalFintess(0),
                                                        maxCoefficientValue_(3),
                                                        optParams_(optParams),
                                                        elitesCount_(3),
                                                        continueOptimization_(true),
                                                        simulationParams_(params),
                                                        simulationScheduler_(nullptr),
                                                        fitnessModel_(nullptr)
    {
        simulationScheduler_ = new SimulationScheduler(simulationParams_);
        fitnessModel_ = new FitnessModel(optParams_.fitness);
        scrambler_ = new SingleCrossoverMultiMutationScrambler(optParams_.geneticOptimizer);
        QObject::connect(simulationScheduler_, SIGNAL(simulationFinished()), this, SLOT(simulationBatchComplete()),Qt::DirectConnection);
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
    bool isRunning()
    {
        return simRunning_ || continueOptimization_;
        //return !simulationScheduler_->IsTasksFinished();
    }


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
