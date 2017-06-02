#include "optimizer/genetic/genome_scrambler.h"

#include <cstdlib>

void DudScrambler::Mutate(Genome *genome)
{
    char *bytesArray = genome->getCoefficientsArray();

    if(bytesArray != nullptr)
    {
        //Calculate how many bites will be mutated
        int bytesCount = rand() % 20 + 4;
        int currentBitNumber;
        int currentBitValue;

        for(int i =0; i < bytesCount; ++i)
        {
            currentBitNumber = rand()%strlen(bytesArray);
            currentBitValue = rand()%10;

            if(currentBitValue >=7)
                bytesArray[currentBitNumber] = 0;
            else
                bytesArray[currentBitNumber] = 1;
        }
    }
}

Genome* DudScrambler::Crossover(const char *g1, const char*g2)
{
    char *newArray;

    if (strlen(g1) == strlen(g2))
    {
        int arrayLength = strlen(g1);
        int crossoverPoint = rand() % (arrayLength-30)+30;

        newArray = new char[arrayLength];

        for(int i=0; i<arrayLength; ++i)
        {
            if(i > crossoverPoint)
                newArray[i] = g1[i];
            else
                newArray[i] = g2[i];
        }
    }
    else
    {

    }

    //Create new genome
    Genome *child = new Genome();
    child->setBinaryArray(newArray);

    return child;
}
