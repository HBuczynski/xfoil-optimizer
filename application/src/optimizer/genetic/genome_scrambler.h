#ifndef GENOME_SCRAMBLER_H
#define GENOME_SCRAMBLER_H

#include "optimizer/genetic/genome.h"
#include "utility/config.h"
#include <random>

/**
*	@file genome_scrambler.h
*	@brief File providing methods to genome mutation and crossover.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Representation of abstract class.

class GenomeScrambler //This might need rethinking - maybe move to genome as it is genome specific...
{
public:
    virtual Genome * mutate(Genome *genome) = 0;
    virtual Genome* crossover( Genome *g1,  Genome *g2) = 0;
};

//!  Class provides methods to genome reproduction
/*!
  This class can mutate and crossover genomes.
*/
class DudScrambler: public GenomeScrambler
{
public:
   virtual Genome * mutate(Genome *genome) override;
   virtual Genome* crossover( Genome *g1, Genome *g2) override;
};
class SingleCrossoverMultiMutationScrambler : public GenomeScrambler
{
public:
    SingleCrossoverMultiMutationScrambler(const Config::OptimizerParams::GeneticOptimizerParams &params);
    virtual Genome* mutate(Genome *genome) override;
    virtual Genome* crossover(Genome *g1, Genome *g2) override;

private:
    void setBit(uint8_t *genome,int bit, bool val);
    bool getBit(uint8_t *genome, int bit);
    void toggleBit(uint8_t *genome, int bit);

    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> posdist;
    std::uniform_real_distribution<> ddist;
    Config::OptimizerParams::GeneticOptimizerParams params_;
};

#endif // GENOME_SCRAMBLER_H
