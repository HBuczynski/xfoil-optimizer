#pragma once

#include "optimizer/geometry.h"


//!  Class providing basic 2D airfoil geometry representation
/*!
  A more elaborate class description. [TODO]
*/

class Genome
{
public:

    Genome(Geometry &geometry) :    geom_(geometry),
                                    coefficientsCount_(12),
                                    minCoefficientsRange_(0),
                                    maxCoefficientsRange_(5),
                                    maxBitsCount_(255)

    { }

    ~Genome();

    void setCoefficients(AirfoilCoefficients coefficients);
    void setFitness(double value);
    const double &getFitness();

    void convertDoubleCoefficientsToBinary(const AirfoilCoefficients &doubleCoefficients, BinaryAirfoilCoefficients &binaryCoefficients);
    void convertBinaryCoefficientsToDouble(const BinaryAirfoilCoefficients &binaryCoefficients, AirfoilCoefficients &doubleCoefficients);
    void setBinaryVectorFromStruct(const BinaryAirfoilCoefficients &airfoilCoefficients);

private:
    Geometry geom_;

    AirfoilCoefficients doubleCoefficients_;
    BinaryAirfoilCoefficients binaryCoefficients_;

    const int coefficientsCount_;
    const int minCoefficientsRange_;
    const int maxCoefficientsRange_;
    const int maxBitsCount_;
    double fitness_;
};
