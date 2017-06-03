#pragma once

#include "optimizer/geometry.h"
#include "optimizer/genetic/fitness.h"
#include <random>

//!  Class providing basic 2D airfoil geometry representation
/*!
  A more elaborate class description. [TODO]
*/

class Genome
{
public:

    Genome(AirfoilCoefficients coeff);
    Genome(unsigned char *array);
    Genome();

    ~Genome();

    void Set(AirfoilCoefficients &coefficients);
    Geometry* getGeometry();
    void setFitness(double value);
    double &getFitness();
    unsigned char *getCoefficientsArray();
    AirfoilCoefficients getCoefficients();
    uint8_t getRandomByte();
    void Set(BinaryAirfoilCoefficients &airfoilCoefficients);
    void Set(unsigned char *array);
    void Randomize();
private:
    uint8_t convertTobyte(double val);
    double convertTodouble(uint8_t val);
    Geometry *geom_;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> bytedist;
    static bool rngSeeded_;
    BinaryAirfoilCoefficients binaryCoefficients_;

    const double minCoeffRange_;
    const double maxCoeffRange_;

    double fitness_;
};
