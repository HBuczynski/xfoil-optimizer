#pragma once
#include "optimizer/simulation_results.h"
#include "utility/config.h"

/**
*	@file fitness.h
*	@brief This header file contains function to calculate fitness od specific genome.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class maintain fitness function for genetic algorithm
/*!
*  Calculate fitness for each genome in population.
*/
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

