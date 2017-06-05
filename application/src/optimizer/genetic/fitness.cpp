#include "optimizer/genetic/fitness.h"

#include <random>
double FitnessModel::Calculate(const SimResults &results)
{
    //TODO check somehow if results range is viable//
    if(!results.IsCalculated() || results.GetPolarPointCount() < 10)
        return 0.0;
    SimResults::PolarPoint maxCl, minCd, maxGlide;
    double avgTorq;
    maxCl = results.CalcMaxCl();
    maxGlide = results.CalcMaxGlideRatio();
    minCd =results.CalcMinCd();
    avgTorq = results.CalcAvgTorque();
    //Fitness calcilation//
    double fitness = 0.0;

    if(params_.optimizeStall)
    {
        fitness += params_.weightMoment * (15 - abs(params_.targetStallAlfa - maxCl.alfa));//Minimizing, dont allow for overshoot 15 seems good bias
    }
    if(params_.optimizeCl)
    {
        fitness += params_.weightCl * (3.0 - abs(params_.targetCl - maxCl.param));
    }
    if(params_.optimizeGlide)
    {
        fitness += params_.weightGlide * (300 - abs(params_.targetGlide - maxGlide.param));
    }
    if(params_.optimizeGlide)
    {
        fitness += params_.weightCd * (params_.targetCd - minCd.param);//Minimize draag coefficient, allow overshoot
    }
    if(params_.optimizeMoment)
    {
        fitness += params_.optimizeMoment * (0.5 - abs(params_.targetMoment - avgTorq)); // Aim for target torque
    }
    if(fitness <0.0)
        fitness = 0.0;
    return (double)rand() / RAND_MAX *1024.0;
    return fitness;
}
