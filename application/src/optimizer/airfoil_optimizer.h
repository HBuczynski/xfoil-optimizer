#pragma once
#include "optimizer/geometry.h"
#include <QObject>
//!  Interface class for various optimizers
/*!
  Provides an interface for model to control and display results of the optimization
*/
class AirfoilOptimizer: public QObject
{
    Q_OBJECT
public:
    virtual void AddBaseGeometry(Geometry &geom) = 0;
    virtual void OptimizeStep() = 0;
    virtual Geometry const GetTopGeometry(int place) = 0;
    virtual double const GetProgress() = 0;
//public Q_SLOTS:
//    virtual void simulationBatchComplete(){}
//Q_SIGNALS:
//    void optimizationFinished();
};

class DudOptimizer : public AirfoilOptimizer
{
public:
    DudOptimizer(Geometry &geom):
        baseGeom_(geom)
    {

    }
    virtual void AddBaseGeometry(Geometry &geom) override
    {
        baseGeom_ = geom;
    }
    virtual void OptimizeStep() override
    {
        if(progress_ < 1.0)
        {
            progress_ += 0.1;
        }
    }
    virtual Geometry const GetTopGeometry(int place) override
    {
        return baseGeom_;
    }
    virtual double const GetProgress() override
    {
        return progress_;
    }
private:
    Geometry baseGeom_;
    double progress_ = 0.0;
};
