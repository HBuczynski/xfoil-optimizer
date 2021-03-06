#include "optimizer/genetic/genome_scrambler.h"

#include <cstdlib>

SingleCrossoverMultiMutationScrambler::SingleCrossoverMultiMutationScrambler(const Config::OptimizerParams::GeneticOptimizerParams &params) :
    rng(std::random_device()()),
    posdist(1,sizeof(BinaryAirfoilCoefficients) * 8 -1),
    ddist(0.0,1.0),
    params_(params)
{
}


void SingleCrossoverMultiMutationScrambler::setBit(uint8_t *genome,int bit, bool val)
{
    if(val)
        genome[bit/8] = genome[bit/8] | ((uint8_t)1<<(bit%8));
    else
        genome[bit/8] = genome[bit/8] & (~((uint8_t)1<<(bit%8)));
}
void SingleCrossoverMultiMutationScrambler::toggleBit(uint8_t *genome, int bit)
{
     genome[bit/8] = genome[bit/8] ^ ((uint8_t)1<<(bit%8));
}
bool SingleCrossoverMultiMutationScrambler::getBit(uint8_t *genome,int bit)
{
    //return true;
    //std::cout<<(int)genome[0]<<std::endl;
    return (genome[bit/8] & 1);
    //return (genome[bit/8] & (1<<(bit%8))) > 0;
}
Genome *SingleCrossoverMultiMutationScrambler::mutate(Genome *genome)
{
    for(int i = 0; i < sizeof(BinaryAirfoilCoefficients) * 8; ++i)
        if(ddist(rng) < params_.mutationRate)
        {
            toggleBit(genome->getCoefficientsArray(),i);
        }
    genome->reload();
    if(genome->getGeometry()->isProfileCrossed())
    {
        delete genome;
        genome = nullptr;
    }
    return genome;
}
Genome *SingleCrossoverMultiMutationScrambler::crossover(Genome *g1, Genome *g2)
{
    BinaryAirfoilCoefficients child;
    uint8_t *cbuf = reinterpret_cast<uint8_t*>(&child);
   // std::cout<<"Fitness1 - "<<g1->getFitness()<<std::endl;
   // std::cout<<"Fitness2 - "<<g2->getFitness()<<std::endl;
    BinaryAirfoilCoefficients p1 = g1->getBinaryCoefficients(), p2 = g2->getBinaryCoefficients();
    uint8_t *p1buf = reinterpret_cast<uint8_t*>(&p1);
    uint8_t *p2buf = reinterpret_cast<uint8_t*>(&p2);
    int split_pos = posdist(rng);
    for(int i = 0; i < split_pos; ++i)
    {
        setBit(cbuf,i,getBit(p1buf,i));
    }
    //std::cout<<split_pos<<std::endl;
    for(int i = split_pos; i < sizeof(BinaryAirfoilCoefficients) * 8; ++i)
    {
        setBit(cbuf,i,getBit(p2buf,i));
    }
    Genome *childGen = new Genome(cbuf);
   // if(childGen->getGeometry()->isProfileCrossed())
   // {
   //     delete childGen;
   //     return nullptr;
   // }
    return childGen;

}
Genome * DudScrambler::mutate(Genome *genome)
{
    return genome;
}

Genome* DudScrambler::crossover(Genome *g1, Genome *g2)
{
    return nullptr;
}
