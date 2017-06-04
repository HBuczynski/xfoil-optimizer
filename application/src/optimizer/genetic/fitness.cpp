#include "optimizer/genetic/fitness.h"

double FitnessModel::calculate(const SimResults &results)
{
    //TODO check somehow if results range is viable//
    if(!results.isCalculated() || results.getPolarPointCount() < 10)
        return 0.0;
    SimResults::PolarPoint maxCl, minCd, maxGlide;
    double avgTorq;
    maxCl = results.calcMaxCl();
    maxGlide = results.calcMaxGlideRatio();
    minCd =results.calcMinCd();
    avgTorq = results.calcAvgTorque();
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
    return 1.0;
    return fitness;
}
