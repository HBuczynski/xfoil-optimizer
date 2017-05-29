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

    AirfoilCoefficients() : p_u(0),
                        q_u(0),
                        a_u(0),
                        b_u(0),
                        c_u(0),
                        d_u(0),
                        p_l(0),
                        q_l(0),
                        a_l(0),
                        b_l(0),
                        c_l(0),
                        d_l(0)
    {

    }
};

class Geometry
{
public:
    Geometry()
    {
        InitializeCoefficients();
        InitializeVectorX();
    }

    Geometry(std::string filename)
    {
        Load(filename);
        InitializeCoefficients();
        InitializeVectorX();
    }
    void Load(std::string filename);
    void InitializeCoefficients();
    void InitializeVectorX();
    void Save(std::string filename);
    void Normalze();
    void Transform();
    const std::vector<Point> GetPoints();
    const SimResults& GetResults()
    {
        return *simResults_;
    }

    Geometry &operator =(const Geometry &data)
    {
        upperPoints_ = data.upperPoints_;
        lowerPoints_ = data.lowerPoints_;
        vectorX_ = data.vectorX_;

        coefficients_ = data.coefficients_;
        simResults_  = data.simResults_;

        return *this;
    }

private:
    std::vector<Point> upperPoints_;
    std::vector<Point> lowerPoints_;
    std::vector<double> vectorX_;

    AirfoilCoefficients coefficients_;
    const int pointsNumber = 150;

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

