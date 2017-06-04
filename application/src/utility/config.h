#pragma once
#include <map>
#include <boost/variant.hpp>

typedef std::map<std::string, boost::variant<double, std::string, int> > Parameters;


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
        std::string xfoilExecutablePath =  "C:\\Users\\Kub\\Documents\\workspace\\xfoil-optimizer\\xfoil\\win32";
        bool viscousEnable = true;
        int reynoldsNo = 10000000;
        int xfoilTimeout = 40;

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

            double weightCl =1.0;
            double weightCd = 1.0;
            double weightGlide = 1.0;
            double weightStall = 0.5;
            double weightMoment = 0.5;
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

