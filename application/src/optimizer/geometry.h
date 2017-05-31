#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "xfoil/simulation_results.h"
#include "optimizer/geometry_structures.h"

class Geometry
{
public:

    Geometry();
    Geometry(std::string filename);

    void Load(std::string filename);
    void Save(std::string filename);
    void SaveCoefficients(std::string filename);
    void LoadFromCoefficients(std::string filename);
    void CalculateCoefficients();

    void Normalze();
    void Transform();
    void regressionAlgorithm();

    const AirfoilCoefficients& getAifroilCoefficients();
    std::vector<Point> GetPoints();
    const int & getPointsCount();
    bool isProfileCrossed();

    const SimResults& GetResults()
    {
        return *simResults_;
    }

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
    void makeAirfoilClosed();


private:
    std::vector<Point> upperPoints_;
    std::vector<Point> lowerPoints_;
    std::vector<double> vectorX_;

    AirfoilCoefficients coefficients_;
    const int pointsCount = 150;
    const double distanceFromEdgeOfAttack = 0.15;
    const double pointsDensity = 0.00115;

    SimResults *simResults_;
};


