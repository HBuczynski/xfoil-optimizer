#include "optimizer/genetic/genetic.h"

#include <cstdlib>

void GeneticOptimizer::Initialize()
{

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
        population_.push_back(*genome);
    }
}

void GeneticOptimizer::checkGenomeFitness(Genome &genome)
{

}

Genome &GeneticOptimizer::rouletteWheelSelection()
{
    //generate a random number between 0 & total fitness count
    int fitness = totalFintess*1000;
    double slice = (rand() % fitness)/1000;
    //go through the chromosones adding up the fitness so far
    double fitnessSoFar = 0.0;

    for (int i=0; i<populationCount_; i++)
    {
        fitnessSoFar += population_[i].getFitness();
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
