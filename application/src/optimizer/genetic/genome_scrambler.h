#ifndef GENOME_SCRAMBLER_H
#define GENOME_SCRAMBLER_H

#include "optimizer/genetic/genome.h"

class GenomeScrambler //This might need rethinking - maybe move to genome as it is genome specific...
{
public:
    virtual void Mutate(Genome *genome) = 0;
    virtual Genome* Crossover(const char *g1, const char*g2) = 0;
};
class DudScrambler: public GenomeScrambler
{
public:
   virtual void Mutate(Genome *genome) override;
   virtual Genome* Crossover(const char *g1, const char*g2) override;
};

#endif // GENOME_SCRAMBLER_H
