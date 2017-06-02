#pragma once
#include <map>
#include <boost/variant.hpp>

typedef std::map<std::string, boost::variant<double, std::string, int> > Parameters;


class Config
{
public:
    struct Gui
    {

    };

    struct Optimization
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
        struct SimulationParams
        {
            int parallelSimulations = 4;
            std::string xfoilExecutablePath = "./xfoil.exe";

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
    Gui gui;
    Optimization optimization;

};
