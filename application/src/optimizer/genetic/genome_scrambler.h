#ifndef GENOME_SCRAMBLER_H
#define GENOME_SCRAMBLER_H

#include "optimizer/genetic/genome.h"
#include "utility/config.h"
#include <random>
class GenomeScrambler //This might need rethinking - maybe move to genome as it is genome specific...
{
public:
    virtual Genome * Mutate(Genome *genome) = 0;
    virtual Genome* Crossover( Genome *g1,  Genome *g2) = 0;
};
class DudScrambler: public GenomeScrambler
{
public:
   virtual Genome * Mutate(Genome *genome) override;
   virtual Genome* Crossover( Genome *g1, Genome *g2) override;
};
class SingleCrossoverMultiMutationScrambler : public GenomeScrambler
{
public:
    SingleCrossoverMultiMutationScrambler(const Config::OptimizerParams::GeneticOptimizerParams &params);
    virtual Genome* Mutate(Genome *genome) override;
    virtual Genome* Crossover(Genome *g1, Genome *g2) override;
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
