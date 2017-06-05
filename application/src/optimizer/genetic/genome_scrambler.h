#ifndef GENOME_SCRAMBLER_H
#define GENOME_SCRAMBLER_H

#include "optimizer/genetic/genome.h"

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
    virtual void Mutate(Genome *genome) = 0;
    virtual Genome* Crossover(const unsigned char *g1, const unsigned char*g2) = 0;
};

//!  Class provides methods to genome reproduction
/*!
  This class can mutate and crossover genomes.
*/
class DudScrambler: public GenomeScrambler
{
public:
   virtual void Mutate(Genome *genome) override;
   virtual Genome* Crossover(const unsigned char *g1, const unsigned char *g2) override;
};

#endif // GENOME_SCRAMBLER_H
