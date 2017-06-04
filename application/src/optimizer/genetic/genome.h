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
    uint8_t * getCoefficientsArray();
    AirfoilCoefficients getCoefficients();
    BinaryAirfoilCoefficients getBinaryCoefficients();
    uint8_t getRandomByte();
    void Set(BinaryAirfoilCoefficients &airfoilCoefficients);
    void Set(unsigned char *array);
    void Randomize();
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
