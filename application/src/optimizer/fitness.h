#pragma once
#include "optimizer/simulation_results.h"
#include "utility/configuration_reader.h"
class FitnessModel
{
public:
    FitnessModel()
    {}
    double Calculate(const SimResults &results);
private:

};

