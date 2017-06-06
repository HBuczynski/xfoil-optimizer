#pragma once
#include <map>
#include <boost/variant.hpp>

/**
*	@file config.h
*	@brief Class containing parameters for the whole application.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

typedef std::map<std::string, boost::variant<double, std::string, int> > Parameters;

//!  Class containing application parameters
/*!
  This class consists basic structures use in the whole application.
*/
class Config
{
public:
    struct ApplicationParams
    {

    };
    struct SimulationParams
    {
        int parallelSimulations = 4;
        int iterationLimit = 30;
        std::string xfoilExecutablePath =  "C:\\Users\\Hubert\\Documents\\Projekt\\xfoil-optimizer\\xfoil\\win32";
        bool viscousEnable = true;
        int reynoldsNo = 10000000;
        int xfoilTimeout = 15;

    };
    struct OptimizerParams
    {
        struct Fitness
        {
            bool optimizeStall = false;
            bool optimizeCl = true;
            bool optimizeCd = true;
            bool optimizeGlide = false;
            bool optimizeMoment = false;

            double targetCl = 1.3;
            double targetCd = 0.01;
            double targetGlide = 120.0;
            double targetStallAlfa = 12.0;
            double targetMoment = 0.115;

            double weightCl =1000.0;
            double weightCd = 500.0;
            double weightGlide = 1000.0;
            double weightStall = 500.0;
            double weightMoment = 100.0;
        };
        struct GeneticOptimizerParams
        {
            int generationCount = 20;
            int populationSize = 100;
            double mutationRate = 0.005;
        };


        enum OptimizerType
        {
            Genetic
        };
        Fitness fitness;
        OptimizerType optimizerType = Genetic;
        GeneticOptimizerParams geneticOptimizer;
        SimulationParams simulation;
    };
    // Config contains //
    //Gui gui;
    //Optimization optimization;

};

