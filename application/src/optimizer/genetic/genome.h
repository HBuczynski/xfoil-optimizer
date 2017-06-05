#pragma once

#include "optimizer/geometry.h"
#include "optimizer/genetic/fitness.h"
#include <random>

/**
*	@file genome.h
*	@brief Class providing basic 2D airfoil geometry representation.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class contains implementation of the genome
/*!
*  Genome is a representation of one instance of population.
*/
class Genome
{
public:

    Genome(AirfoilCoefficients coeff);
    Genome(unsigned char *array);
    Genome();

    ~Genome();

    void set(AirfoilCoefficients &coefficients);
    void setFitness(double value);
    void set(BinaryAirfoilCoefficients &airfoilCoefficients);
    void set(unsigned char *array);

    Geometry* getGeometry();
    double &getFitness();
    uint8_t * getCoefficientsArray();
    AirfoilCoefficients getCoefficients();
    BinaryAirfoilCoefficients getBinaryCoefficients();
    uint8_t getRandomByte();

    void randomize();
    void reload();

    BinaryAirfoilCoefficients binaryCoefficients_;

private:
    uint8_t convertTobyte(double val);
    double convertTodouble(uint8_t val);

    Geometry *geom_;

    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> bytedist;

    const double minCoeffRange_;
    const double maxCoeffRange_;

    double fitness_;
};
