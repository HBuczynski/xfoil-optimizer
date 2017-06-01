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

        struct GeneticOptimizerParams
        {
            enum CrossoverMethod
            {
                SinglepointCrossover,
                MultipointCrossover,
                UniformCrossover
            };
            enum MutationMethod
            {
                FlipbitMutation,
                UniformMutation
            };
            MutationMethod mutationMethod = FlipbitMutation;
            CrossoverMethod crossoverMethod = SinglepointCrossover;
            double mutationRate = 0.1;
        };

        enum OptimizerType
        {
            Genetic
        };
        OptimizerType optimizerType = Genetic;
        GeneticOptimizerParams geneticOptimizer;
        SimulationParams simulation;
    };
    // Config contains //
    //Gui gui;
    //Optimization optimization;

};

