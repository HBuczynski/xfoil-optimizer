#include "optimizer/genetic/genome.h"

int Genome::currentCoefficientCount_ = 0;

Genome::~Genome()
{

}

void Genome::setCoefficients(AirfoilCoefficients coefficients)
{
    doubleCoefficients_ = coefficients;
    convertDoubleCoefficientsToBinary(doubleCoefficients_, binaryCoefficients_);
}

void Genome::setFitness(double value)
{
    fitness_ = value;
}

const double &Genome::getFitness()
{
    return fitness_;
}

void Genome::convertDoubleCoefficientsToBinary(const AirfoilCoefficients &doubleCoefficients, BinaryAirfoilCoefficients &binaryCoefficients)
{

}

void Genome::convertBinaryCoefficientsToDouble(const BinaryAirfoilCoefficients &binaryCoefficients, AirfoilCoefficients &doubleCoefficients)
{

}


