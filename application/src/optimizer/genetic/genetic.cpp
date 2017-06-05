#include "optimizer/genetic/genetic.h"

#include <cstdlib>
#include <map>

GeneticOptimizer::GeneticOptimizer(Config::SimulationParams &params, Config::OptimizerParams &optParams):
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

GeneticOptimizer::~GeneticOptimizer()
{
    if(simulationScheduler_ != nullptr)
        delete simulationScheduler_;
    if(fitnessModel_ != nullptr)
        delete fitnessModel_;
    delete scrambler_;
}

void GeneticOptimizer::initialize(Geometry &baseGeometry_)
{
    for(auto genome: population_)
        delete genome;
    population_.clear();
    AirfoilCoefficients baseCoeff = baseGeometry_.getAifroilCoefficients();
    int newGenomeNumber = 0;
    //newGenomeNumber = optParams_.geneticOptimizer.populationSize;
    while(newGenomeNumber < optParams_.geneticOptimizer.populationSize)
    {
       // std::cout<<"next iteration bef cross"<<currentIterationNumber_<<std::endl;
        Genome *newGenome = new Genome(baseCoeff);
       // std::cout<<"next iteration afterbef cross"<<newGenomeNumber<<std::endl;
        if(newGenome != nullptr)
        {
            newGenome = scrambler_->mutate(newGenome);
            if(newGenome != nullptr)
            {
                population_.push_back(newGenome);
                newGenome = nullptr;
                ++newGenomeNumber;
            }
        }
    }
    state_ = Initialized;
}

void GeneticOptimizer::runGeneticAlgorithm()
{
    if(state_ == NotInitialized)
        generateInitialPopulation();
    totalFintess = 0;
    //start simulation of each genome
    //std::cout<<"Starting to playyy"<<std::endl;
    std::vector<Task> tasks;

    for(auto genome: population_)
        tasks.push_back(Task(genome->getGeometry()));
    simulationScheduler_->addBatchTask(tasks);
    state_ = SimulationInProgress;
    simRunning_ = true;
    //std::cout<<"Running"<<std::endl;
}
void GeneticOptimizer::optimizeStep()
{
    //int currentIterationNumber = 0;
    int newGenomeNumber = 0;
    //simulationScheduler_->WaitForFinished();
    if(!simulationScheduler_->isTasksFinished())
        throw std::out_of_range("Should be finifhed task");
    calculateFitness();

    //check to see if algoirthm find any solution
    for(auto genome : population_)
    {
        totalFintess += genome->getFitness();
        if(checkGenomeFitness(genome))
        {
            state_ = OptimizationCompleteTargetReached;
            std::cout<<"Optimization Finished - targets reached"<<std::endl;
            continueOptimization_ = false;
            return;
        }
    }
    ++currentIterationNumber_;

    if(continueOptimization_ && currentIterationNumber_ < optParams_.geneticOptimizer.generationCount)
    {
        newGenomeNumber = 0;
        //newGenomeNumber = optParams_.geneticOptimizer.populationSize;
        while(newGenomeNumber < optParams_.geneticOptimizer.populationSize)
        {
           // std::cout<<"next iteration bef cross"<<currentIterationNumber_<<std::endl;
            Genome *newGenome = scrambler_->crossover(rouletteWheelSelection(), rouletteWheelSelection());
           // std::cout<<"next iteration afterbef cross"<<newGenomeNumber<<std::endl;
            if(newGenome != nullptr)
            {
                newGenome = scrambler_->mutate(newGenome);
                if(newGenome != nullptr)
                {
                    tempPopulation.push_back(newGenome);
                    newGenome = nullptr;
                    ++newGenomeNumber;
                }
            }
        }

        createPopulationAfterReproduction();
        totalFintess = 0;
        std::vector<Task> tasks;

        for(auto genome: population_)
            tasks.push_back(Task(genome->getGeometry()));
        simulationScheduler_->addBatchTask(tasks);
        state_ = SimulationInProgress;
        simRunning_ = true;
    }
    else
    {
        Q_EMIT optimizationFinished();
        continueOptimization_ = false;
        state_ = OptimizationCompleteFinalGeneration;
        std::cout<<"Optimization Finished - population count reached"<<std::endl;
    }
}

const Geometry GeneticOptimizer::getTopGeometry(int place)
{
    //TODO//
    return baseGeometry_;
}

const double GeneticOptimizer::getProgress()
{
    return 0.0;
}

bool GeneticOptimizer::isRunning()
{
    return simRunning_ || continueOptimization_;
    //return !simulationScheduler_->IsTasksFinished();
}

GeneticOptimizer::GAState GeneticOptimizer::getState()
{
    return state_;
}


void GeneticOptimizer::requestStop()
{
    continueOptimization_ = false;
}

void GeneticOptimizer::generateInitialPopulation()
{
    int i=0;
    while( i < optParams_.geneticOptimizer.populationSize )
    {
        Genome *genome = new Genome();

        if(genome->getGeometry()->isProfileCrossed())
        {
            delete genome;
        }
        else
        {
            population_.push_back(genome);
            ++i;
        }
    }
}

void GeneticOptimizer::addGenomeToElite(Genome *genome)
{
    for(auto iter = elites_.begin(); iter != elites_.end(); ++iter )
    {
        if(genome->getFitness() > (*iter)->getFitness())
        {
           Genome *gen = *iter;
           delete gen;
           elites_.erase(iter);
           elites_.push_back(genome);
        }
    }
}

void GeneticOptimizer::addGenomeToPopulation(Genome *genome)
{
    for(auto iter = population_.begin(); iter != population_.end(); ++iter )
    {
        if(genome->getFitness() > (*iter)->getFitness())
        {
           Genome *gen = *iter;
           delete gen;
           population_.erase(iter);
           population_.push_back(genome);
        }
    }
}

void GeneticOptimizer::createPopulationAfterReproduction()
{
    std::multimap<double, Genome*> aggregatePopulation;

    for(auto iter = population_.begin(); iter != population_.end(); ++iter )
    {
        Genome *gen = *iter;
        aggregatePopulation.insert(std::make_pair(gen->getFitness(), gen));
    }

    for(auto iter = tempPopulation.begin(); iter != tempPopulation.end(); ++iter )
    {
        Genome *gen = *iter;
        aggregatePopulation.insert(std::make_pair(gen->getFitness(), gen));
    }

    population_.clear();
    tempPopulation.clear();

    int i=0;
    for(auto iter = aggregatePopulation.rbegin(); (iter != aggregatePopulation.rend()); ++iter)
    {
        if(i<optParams_.geneticOptimizer.populationSize)
            population_.push_back(iter->second);
        else
            delete iter->second;
        ++i;
    }
    std::cout<<"New population count is :"<<i<<std::endl;
}

bool GeneticOptimizer::checkGenomeFitness(Genome *genome)
{
    //TO DO: check if we find solution
    return false;
}

void GeneticOptimizer::calculateFitness()
{
    for(auto genome : population_)
    {
        genome->setFitness(fitnessModel_->calculate(genome->getGeometry()->getResults()));

    }
}

Genome *GeneticOptimizer::rouletteWheelSelection()
{
    //generate a random number between 0 & total fitness count
    int fitness = totalFintess;
    double slice = (double)(rand() % fitness);
    //go through the chromosones adding up the fitness so far
    double fitnessSoFar = 0.0;
    Genome *selectedGenome;
    std::random_shuffle(population_.begin(), population_.end());

    for (int i=0; i<optParams_.geneticOptimizer.populationSize; i++)
    {
        fitnessSoFar += population_[i]->getFitness();
        //std::cout<<population_[i]->getFitness()<<std::endl;
        //if the fitness so far > random number return the chromo at this point
        if (fitnessSoFar >= slice)
        {
            //std::cout<<"Selected genome no" << i<<std::endl;
            selectedGenome = population_[i];
            break;
        }
    }
    //totalFintess = 0;
    return selectedGenome;
}
//Slots//
void GeneticOptimizer::simulationBatchComplete()
{
    //std::cout<<"Next Population?"<<std::endl;
    bool wasRunning = simRunning_;
    simRunning_ = false;
    if(wasRunning)
    {
        state_ = GenerationComplete;
        optimizeStep();
    }
}
