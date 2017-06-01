#pragma once

#include "optimizer/geometry.h"


//!  Class providing basic 2D airfoil geometry representation
/*!
  A more elaborate class description. [TODO]
*/

class Genome
{
public:

    Genome() :    coefficientsCount_(12),
                  minCoefficientsRange_(0),
                  maxCoefficientsRange_(5),
                  maxBitsCount_(255),
                  binaryCoefficientsArray_(nullptr)


    { }

    ~Genome();

    void setCoefficients(AirfoilCoefficients coefficients);
    void setFitness(double value);
    void setBinaryArray(char *array);
    const double &getFitness();

    void convertDoubleCoefficientsToBinary(const AirfoilCoefficients &doubleCoefficients, BinaryAirfoilCoefficients &binaryCoefficients);
    void convertBinaryCoefficientsToDouble(const BinaryAirfoilCoefficients &binaryCoefficients, AirfoilCoefficients &doubleCoefficients);
    void setBinaryArrayFromStruct(const BinaryAirfoilCoefficients &airfoilCoefficients);
    void setStructFromBinaryArray(const char *array);

    char *getCoefficientsArray();

private:
    Geometry geom_;

    AirfoilCoefficients doubleCoefficients_;
    BinaryAirfoilCoefficients binaryCoefficients_;
    char *binaryCoefficientsArray_;

    const int coefficientsCount_;
    const int minCoefficientsRange_;
    const int maxCoefficientsRange_;
    const int maxBitsCount_;
    double fitness_;
};
