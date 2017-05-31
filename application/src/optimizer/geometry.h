#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "xfoil/simulation_results.h"

class Point;
struct AirfoilCoefficients
{
    double p_u;
    double q_u;
    double a_u;
    double b_u;
    double c_u;
    double d_u;

    double p_l;
    double q_l;
    double a_l;
    double b_l;
    double c_l;
    double d_l;

    AirfoilCoefficients() : p_u(-100),
                            q_u(-100),
                            a_u(-100),
                            b_u(-100),
                            c_u(-100),
                            d_u(-100),
                            p_l(-100),
                            q_l(-100),
                            a_l(-100),
                            b_l(-100),
                            c_l(-100),
                            d_l(-100)
    {

    }
};

class Geometry
{
public:
    Geometry()
    {
        CalculateCoefficients();
        calculateCordinateOfX();
    }

    Geometry(std::string filename)
    {
        Load(filename);
        CalculateCoefficients();
    }
    void Load(std::string filename);
    void CalculateCoefficients();
    void SaveCoefficients(std::string filename);
    void LoadFromCoefficients(std::string filename);
    void Save(std::string filename);
    void Normalze();
    void Transform();
    const AirfoilCoefficients& getAifroilCoefficients();
    std::vector<Point> GetPoints();

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
    bool isProfileCrosses();

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
class Point
{
public:
    Point(double xin, double yin) :
        x(xin),
        y(yin)
    {}
    Point() :
        x(0.0),
        y(0.0)
    {}

    double x;
    double y;
};

inline bool operator==(const Point& lhs, const Point& rhs)
{
    double eps = 0.00000001;
    if(abs(lhs.x - rhs.x) < eps && abs(lhs.y - rhs.y) < eps)
        return true;
    return false;
}

