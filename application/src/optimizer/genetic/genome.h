#pragma once

#include "optimizer/geometry.h"


//!  Class providing basic 2D airfoil geometry representation
/*!
  A more elaborate class description. [TODO]
*/

class Genome
{
public:

    typedef std::uint8_t byte;

    Genome(Geometry &geometry) :    geom_(geometry),
                                    coefficientsCount_(12),
                                    binaryChromosom_(new byte[coefficientsCount_])
    { }

    void setFitness(double value);
    const double &getFitness();
    const byte &getChromosom();

    ~Genome();

private:
    Geometry geom_;

    byte *binaryChromosom_;
    static int currentCoefficientCount_;
    const int coefficientsCount_;
    double fitness_;
};
