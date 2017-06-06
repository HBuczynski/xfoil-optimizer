#pragma once
#include "optimizer/geometry.h"
#include <QObject>

/**
*	@file airfoil_optimizer.h
*	@brief Interface class for various optimizers.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/
//! \class AirfoilOptimizer
//! \brief  Abstract Airfoil optimizer object for managing Optimization and communication with model
/*!
*  Allows for multiple optimizer implementations
*/
class AirfoilOptimizer: public QObject
{
    Q_OBJECT
public:
    virtual void initialize(Geometry &geom) = 0;
    virtual void optimizeStep() = 0;
    virtual Geometry const getTopGeometry(int place) = 0;
    virtual double const getProgress() = 0;
//public Q_SLOTS:
//    virtual void simulationBatchComplete(){}
Q_SIGNALS:
    void optimizationFinished();
};
//! \class DudOptimizer
//! \brief  Dud Airfoil optimizer object for testing interfaces
/*!
*  Allows for different test scenarios
*/
class DudOptimizer : public AirfoilOptimizer
{
public:
    DudOptimizer(Geometry &geom):
        baseGeom_(geom)
    {

    }
    virtual void initialize(Geometry &geom) override
    {
        baseGeom_ = geom;
    }
    virtual void optimizeStep() override
    {
        if(progress_ < 1.0)
        {
            progress_ += 0.1;
        }
    }
    virtual Geometry const getTopGeometry(int place) override
    {
        return baseGeom_;
    }
    virtual double const getProgress() override
    {
        return progress_;
    }
private:
    Geometry baseGeom_;
    double progress_ = 0.0;
};
