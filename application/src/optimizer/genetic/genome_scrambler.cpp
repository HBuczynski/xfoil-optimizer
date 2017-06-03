#include "optimizer/genetic/genome_scrambler.h"

#include <cstdlib>

void DudScrambler::Mutate(Genome *genome)
{
    unsigned char *bytesArray = genome->getCoefficientsArray();

    if(bytesArray != nullptr)
    {
        //Calculate how many bites will be mutated
        int bytesCount = rand() % 20 + 4;
        int currentBitNumber;
        int currentBitValue;

        for(int i =0; i < bytesCount; ++i)
        {
            currentBitNumber = rand()% sizeof(bytesArray)*8;
            currentBitValue = rand()%10;

            if(currentBitValue >=7)
                bytesArray[currentBitNumber] = 0;
            else
                bytesArray[currentBitNumber] = 1;
        }
    }
}

Genome* DudScrambler::Crossover(const unsigned char *g1, const unsigned char*g2)
{
    unsigned char *newArray;

    bool profileIsCrossed = true;

    while(profileIsCrossed)
    {
        int arrayLength = sizeof(g1)*8;
        int crossoverPoint = rand() % (arrayLength-30)+30;

        newArray = new unsigned char[arrayLength];

        for(int i=0; i<arrayLength; ++i)
        {
            if(i > crossoverPoint)
                newArray[i] = g1[i];
            else
                newArray[i] = g2[i];
        }

        //Create new genome
        Genome *genome = new Genome(newArray);
        profileIsCrossed = genome->getGeometry()->isProfileCrossed();

        if(profileIsCrossed)
            delete genome;
        else
            return genome;
    }
    //ERROR//
    return nullptr;
}
