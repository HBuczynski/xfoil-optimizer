#include "optimizer/simulation_results.h"

#include <iostream>
SimResults::PolarPoint SimResults::CalcMaxCl() const
{
    if(!IsCalculated() || results_.size() == 0)
        throw std::out_of_range("No result datapoints");
    PolarPoint maxCl;
    maxCl.alfa = results_.front().alfa;
    maxCl.param = results_.front().cl;
    for(ResultEntry entry: results_)
    {
        if(entry.cl > maxCl.param)
        {
            maxCl.alfa = entry.alfa;
            maxCl.param = entry.cl;
        }
    }

    return maxCl;
}

SimResults::PolarPoint SimResults::CalcMinCd() const
{
    if(!IsCalculated() || results_.size() == 0)
        throw std::out_of_range("No result datapoints");
    PolarPoint minCd;
    minCd.alfa = results_.front().alfa;
    minCd.param = results_.front().cd;
    for(ResultEntry entry: results_)
    {
        if(entry.cl < minCd.param)
        {
            minCd.alfa = entry.alfa;
            minCd.param = entry.cd;
        }
    }

    return minCd;
}
SimResults::PolarPoint SimResults::CalcMaxGlideRatio() const
{
    if(!IsCalculated() || results_.size() == 0)
        throw std::out_of_range("No result datapoints");

    PolarPoint ratio;
    ratio.alfa = results_.front().alfa;
    ratio.param = results_.front().cl / results_.front().cd;
    for(ResultEntry entry: results_)
    {
        double tmp = entry.cl / entry.cd;
        if(tmp > ratio.param)
        {
            ratio.alfa = entry.alfa;
            ratio.param = tmp;
        }
    }

    return ratio;
}
double SimResults::CalcAvgTorque() const
{
    if(!IsCalculated() || results_.size() == 0)
        throw std::out_of_range("No result datapoints");

}
