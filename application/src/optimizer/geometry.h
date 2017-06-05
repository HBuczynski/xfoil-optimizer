#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "optimizer/simulation_results.h"
#include "optimizer/geometry_structures.h"

/**
*	@file geometry.h
*	@brief File consists representation of airfoil geometry.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

//!  Class providing necessary attributes for geometry calculation
/*!
  This class provides loading and saving profile to file.
*/
class Geometry
{
    friend class SimulationHandler;//This will write to results file
public:

    Geometry();
    Geometry(AirfoilCoefficients coeff);
    Geometry(std::string filename);

    void load(std::string filename);
    void save(std::string filename);

    void saveCoefficients(std::string filename);
    void loadFromCoefficients(std::string filename);
    void calculateCoefficients();
    void createNewGeometry(AirfoilCoefficients coeff);

    void normalize();
    void transform();
    void regressionAlgorithm();

    const AirfoilCoefficients& getAifroilCoefficients();
    std::vector<Point> getPoints();
    const int & getPointsCount();
    bool isProfileCrossed();
    const SimResults& getResults();

    Geometry &operator =(const Geometry &data)
    {
        this->upperPoints_ = data.upperPoints_;
        lowerPoints_ = data.lowerPoints_;

        coefficients_ = data.coefficients_;
        simResults_  = data.simResults_;

        return *this;
    }

private:
    void calculateCordinateOfX();

private:
    std::vector<Point> upperPoints_;
    std::vector<Point> lowerPoints_;
    std::vector<double> vectorX_;

    AirfoilCoefficients coefficients_;
    const int pointsCount = 150;
    const double distanceFromEdgeOfAttack = 0.15;
    const double pointsDensity = 0.00115;

    SimResults simResults_;
};


