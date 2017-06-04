#pragma once
#include "optimizer/simulation_results.h"
#include "utility/config.h"
class FitnessModel
{
public:
    FitnessModel(Config::OptimizerParams::Fitness params):
        params_(params)
    {}
    double calculate(const SimResults &results);
private:
    const Config::OptimizerParams::Fitness params_;
};

