#include "optimizer/genetic/genome.h"

Genome::~Genome()
{
    delete[] binaryChromosom_;
}

const double &Genome::getFitness()
{
    return fitness_;
}
