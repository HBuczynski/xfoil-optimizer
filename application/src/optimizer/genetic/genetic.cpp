#include "optimizer/genetic/genetic.h"

#include <cstdlib>

void GeneticOptimizer::Initialize()
{

}

void GeneticOptimizer::runGeneticAlgorithm()
{
    //generate basic population for first interation
    //function calculate fitness simultaneously
    generateInitialPopulation();

    int currentIterationNumber = 0;
    int newGenomeNumber = 0;
    //some temporary storage for the new population we are about to create in while loop
    std::vector<Genome*> tempPopulation;

    while(continueOptimization_ || currentIterationNumber < iterationNumber_)
    {
        totalFintess = 0;

        for(auto genome : population_)
        {
            totalFintess += genome->getFitness();
            //check to see if algoirthm find any solution
            if(checkGenomeFitness(genome))
            {
                continueOptimization_ = false;
                return;
            }
        }

        while(newGenomeNumber < populationCount_)
        {
            Genome *newGenome = scrambler_.Crossover(rouletteWheelSelection()->getCoefficientsArray(), rouletteWheelSelection()->getCoefficientsArray());
            scrambler_.Mutate(newGenome);

            newGenome->calculateFitness();
            tempPopulation.push_back(newGenome);

            //copy temp population to main population

            //save some genome to elite

           ++newGenomeNumber;
        }

         ++currentIterationNumber;
    }
}

GeneticOptimizer::GAState GeneticOptimizer::GetState() const
{
    return state_;
}

void GeneticOptimizer::generateInitialPopulation()
{
    for(int i=0; i<populationCount_; ++i)
    {
        Genome *genome = new Genome();
        genome->setCoefficients(generateRandomCoefficients());
        genome->calculateFitness();
        population_.push_back(genome);
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

bool GeneticOptimizer::checkGenomeFitness(Genome *genome)
{
    //TO DO: check if we find solution
    return true;
}

Genome *GeneticOptimizer::rouletteWheelSelection()
{
    //generate a random number between 0 & total fitness count
    int fitness = totalFintess*1000;
    double slice = (rand() % fitness)/1000;
    //go through the chromosones adding up the fitness so far
    double fitnessSoFar = 0.0;

    for (int i=0; i<populationCount_; i++)
    {
        fitnessSoFar += population_[i]->getFitness();
        //if the fitness so far > random number return the chromo at this point
        if (fitnessSoFar >= slice)
            return population_[i];
    }
}

AirfoilCoefficients GeneticOptimizer::generateRandomCoefficients()
{
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
