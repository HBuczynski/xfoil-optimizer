#include "optimizer/fitness.h"

double FitnessModel::Calculate(const SimResults &results)
{
    SimResults::PolarPoint maxCl, minCd, maxGlide;
    double avgTorq;
    maxCl = results.CalcMaxCl();
    maxGlide = results.CalcMaxGlideRatio();
    minCd =results.CalcMinCd();
    avgTorq = results.CalcAvgTorque();

    //TMP values//
    bool oStall, oCl, oGlide, oCd, oTorq;
    double tStall, tCl, tGlide, tCd, tTorq;
    double wStall, wCl, wGlide, wCd, wTorq;
    //Fitness calcilation//
    double fitness = 0.0;

    if(oStall)
    {
        fitness += wStall * (15 - abs(tStall - maxCl.alfa));//Minimizing, dont allow for overshoot 15 seems good bias
    }
    if(oCl)
    {
        fitness += wCl * (3.0 - abs(tCl - maxCl.param));
    }
    if(oGlide)
    {
        fitness += wGlide * (300 - abs(tGlide - maxGlide.param));
    }
    if(oCd)
    {
        fitness += wCd * (tCd - minCd.param);//Minimize draag coefficient, allow overshoot
    }
    if(oTorq)
    {
        fitness += wTorq * (0.5 - abs(tTorq - avgTorq)); // Aim for target torque
    }
    return fitness;
}
