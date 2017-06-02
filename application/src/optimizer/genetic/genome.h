#pragma once

#include "optimizer/geometry.h"
#include "optimizer/genetic/fitness.h"


//!  Class providing basic 2D airfoil geometry representation
/*!
  A more elaborate class description. [TODO]
*/

class Genome
{
public:

    Genome(AirfoilCoefficients coeff);
    Genome(unsigned char *array);

    ~Genome();

    void setCoefficients(AirfoilCoefficients coefficients);
    void setBinaryArray(unsigned char *array);
    void setFitness(double value);
    Geometry* getGeometry();
    double &getFitness();
    unsigned char *getCoefficientsArray();

private:
    void convertDoubleCoefficientsToBinary(const AirfoilCoefficients &doubleCoefficients, BinaryAirfoilCoefficients &binaryCoefficients);
    void convertBinaryCoefficientsToDouble(const BinaryAirfoilCoefficients &binaryCoefficients, AirfoilCoefficients &doubleCoefficients);
    void setBinaryArrayFromStruct(BinaryAirfoilCoefficients &airfoilCoefficients);
    void setStructFromBinaryArray(unsigned char *array);

private:
    Geometry *geom_;

    AirfoilCoefficients doubleCoefficients_;
    BinaryAirfoilCoefficients binaryCoefficients_;

    unsigned char *binaryCoefficientsArray_;

    const int coefficientsCount_;
    const int minCoefficientsRange_;
    const int maxCoefficientsRange_;
    const int maxBitsCount_;
    double fitness_;
};
