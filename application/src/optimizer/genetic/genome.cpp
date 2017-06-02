#include "optimizer/genetic/genome.h"

Genome::~Genome()
{
    if(binaryCoefficientsArray_ != nullptr)
        delete [] binaryCoefficientsArray_;
}

void Genome::setCoefficients(AirfoilCoefficients coefficients)
{
    doubleCoefficients_ = coefficients;
    convertDoubleCoefficientsToBinary(doubleCoefficients_, binaryCoefficients_);
    setBinaryArrayFromStruct(binaryCoefficients_);
    calculateFitness();
}

void Genome::setBinaryArray(unsigned char *array)
{
    binaryCoefficientsArray_ = array;
    setStructFromBinaryArray(binaryCoefficientsArray_);
    convertBinaryCoefficientsToDouble(binaryCoefficients_, doubleCoefficients_);
    calculateFitness();
}

double &Genome::getFitness()
{
    return fitness_;
}

void Genome::convertDoubleCoefficientsToBinary(const AirfoilCoefficients &doubleCoefficients, BinaryAirfoilCoefficients &binaryCoefficients)
{
    const double scale = (maxCoefficientsRange_-minCoefficientsRange_) / maxBitsCount_;

    binaryCoefficients.a_l = static_cast<byte>(doubleCoefficients.a_l/scale);
    binaryCoefficients.a_u = static_cast<byte>(doubleCoefficients.a_u/scale);
    binaryCoefficients.b_l = static_cast<byte>(doubleCoefficients.b_l/scale);
    binaryCoefficients.b_u = static_cast<byte>(doubleCoefficients.b_u/scale);
    binaryCoefficients.c_l = static_cast<byte>(doubleCoefficients.c_l/scale);
    binaryCoefficients.c_u = static_cast<byte>(doubleCoefficients.c_u/scale);
    binaryCoefficients.d_l = static_cast<byte>(doubleCoefficients.d_u/scale);
    binaryCoefficients.d_u = static_cast<byte>(doubleCoefficients.d_l/scale);
    binaryCoefficients.q_l = static_cast<byte>(doubleCoefficients.q_l/scale);
    binaryCoefficients.q_u = static_cast<byte>(doubleCoefficients.q_u/scale);
    binaryCoefficients.p_l = static_cast<byte>(doubleCoefficients.p_l/scale);
    binaryCoefficients.p_u = static_cast<byte>(doubleCoefficients.p_u/scale);
}

void Genome::convertBinaryCoefficientsToDouble(const BinaryAirfoilCoefficients &binaryCoefficients, AirfoilCoefficients &doubleCoefficients)
{
    const double scale = (maxCoefficientsRange_-minCoefficientsRange_) / maxBitsCount_;

    doubleCoefficients.a_l = binaryCoefficients.a_l*scale;
    doubleCoefficients.a_u = binaryCoefficients.a_u*scale;
    doubleCoefficients.b_l = binaryCoefficients.b_l*scale;
    doubleCoefficients.b_u = binaryCoefficients.b_u*scale;
    doubleCoefficients.c_l = binaryCoefficients.c_l*scale;
    doubleCoefficients.c_u = binaryCoefficients.c_u*scale;
    doubleCoefficients.d_l = binaryCoefficients.d_l*scale;
    doubleCoefficients.d_u = binaryCoefficients.d_u*scale;
    doubleCoefficients.p_l = binaryCoefficients.p_l*scale;
    doubleCoefficients.p_u = binaryCoefficients.p_u*scale;
    doubleCoefficients.q_l = binaryCoefficients.q_l*scale;
    doubleCoefficients.q_u = binaryCoefficients.q_u*scale;
}
void Genome::setBinaryArrayFromStruct(BinaryAirfoilCoefficients &airfoilCoefficients)
{
    binaryCoefficientsArray_ = new unsigned char[sizeof(BinaryAirfoilCoefficients)];
    binaryCoefficientsArray_ = reinterpret_cast<uint8_t*>(&airfoilCoefficients);
}

void Genome::setStructFromBinaryArray(unsigned char *array)
{
    binaryCoefficients_ = reinterpret_cast<BinaryAirfoilCoefficients&>(array);
}

unsigned char *Genome::getCoefficientsArray()
{
    return binaryCoefficientsArray_;
}

void Genome::calculateFitness()
{

}
