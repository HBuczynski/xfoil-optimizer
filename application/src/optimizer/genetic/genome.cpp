#include "optimizer/genetic/genome.h"

int Genome::currentCoefficientCount_ = 0;

Genome::~Genome()
{
    delete[] binaryChromosom_;
}

void Genome::addCoefficients()
{

}

void Genome::setFitness(double value)
{
    fitness_ = value;
}

const double &Genome::getFitness()
{
    return fitness_;
}

const Genome::byte &Genome::getChromosom()
{
    return *binaryChromosom_;
}

