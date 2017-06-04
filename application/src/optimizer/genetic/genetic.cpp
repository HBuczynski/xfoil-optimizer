#include "optimizer/genetic/genetic.h"

#include <cstdlib>
#include <map>

GeneticOptimizer::~GeneticOptimizer()
{
    if(simulationScheduler_ != nullptr)
        delete simulationScheduler_;
    if(fitnessModel_ != nullptr)
        delete fitnessModel_;
}

void GeneticOptimizer::initialize()
{

}

void GeneticOptimizer::runGeneticAlgorithm()
{
    generateInitialPopulation();

    totalFintess = 0;
    //start simulation of each genome
    for(auto genome: population_)
        simulationScheduler_->AddTask(Task(genome->getGeometry()));
}
void GeneticOptimizer::OptimizeStep()
{
    //int currentIterationNumber = 0;
    int newGenomeNumber = 0;
    //simulationScheduler_->WaitForFinished();
    if(!simulationScheduler_->IsTasksFinished())
        throw std::out_of_range("Should be finifhed task");
    calculateFitness();
    //check to see if algoirthm find any solution
    for(auto genome : population_)
    {
        totalFintess += genome->getFitness();
        if(checkGenomeFitness(genome))
        {
            continueOptimization_ = false;
            return;
        }
    }
    ++currentIterationNumber_;

    if(continueOptimization_ && currentIterationNumber_ < iterationLimit_)
    {
        while(newGenomeNumber < populationCount_)
        {
            Genome *newGenome = scrambler_.Crossover(rouletteWheelSelection()->getCoefficientsArray(), rouletteWheelSelection()->getCoefficientsArray());
            scrambler_.Mutate(newGenome);
            tempPopulation.push_back(newGenome);
            ++newGenomeNumber;
        }
        createPopulationAfterReproduction();
    }
    else
        Q_EMIT optimizationFinished();

}

GeneticOptimizer::GAState GeneticOptimizer::GetState()
{
    return state_;
}

void GeneticOptimizer::generateInitialPopulation()
{
    int i=0;
    std::cout <<"Generate initial population"<<std::endl;
    while( i < populationCount_ )
    {
        std::cout <<"Generate initial population2"<<std::endl;
        Genome *genome = new Genome(generateRandomCoefficients());

        if(genome->getGeometry()->isProfileCrossed())
        {
            delete genome;
        }
        else
        {
            //calculateFitness();
            population_.push_back(genome);
            ++i;
        }
    }
    std::cout <<"Generated initial population"<<std::endl;
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
        if(i<populationCount_)
            population_.push_back(iter->second);
        else
            delete iter->second;
        ++i;
    }

}

bool GeneticOptimizer::checkGenomeFitness(Genome *genome)
{
    //TO DO: check if we find solution
    return true;
}

void GeneticOptimizer::calculateFitness()
{
    for(auto genome : population_)
    {
        genome->setFitness(fitnessModel_->Calculate(genome->getGeometry()->GetResults()));
    }
}

Genome *GeneticOptimizer::rouletteWheelSelection()
{
    //generate a random number between 0 & total fitness count
    int fitness = totalFintess*1000;
    double slice = (rand() % fitness)/1000;
    //go through the chromosones adding up the fitness so far
    double fitnessSoFar = 0.0;
    Genome *selectedGenome;

    for (int i=0; i<populationCount_; i++)
    {
        fitnessSoFar += population_[i]->getFitness();
        //if the fitness so far > random number return the chromo at this point
        if (fitnessSoFar >= slice)
        {
            selectedGenome = population_[i];
            break;
        }
    }

    return selectedGenome;
}

AirfoilCoefficients GeneticOptimizer::generateRandomCoefficients()
{
        std::cout<< "rand()";
    AirfoilCoefficients randomCoefficients;

    randomCoefficients.a_l = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.a_u = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.b_l = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.b_u = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.c_l = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.c_u = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.d_l = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.d_u = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.p_l = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.p_u = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.q_l = (rand() % (maxCoefficientValue_*100)) / 100;
    randomCoefficients.q_u = (rand() % (maxCoefficientValue_*100)) / 100;

    return randomCoefficients;
}
//Slots//
void GeneticOptimizer::simulationBatchComplete()
{
    std::cout<<"Signal received"<<std::endl;

}
