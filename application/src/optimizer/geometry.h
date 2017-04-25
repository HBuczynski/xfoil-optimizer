#pragma once
#include <vector>
#include "xfoil/simulation_results.h"

class Point;
class Geometry
{
public:
    Geometry()
    {}
    void Load();
    void Save();
    void Normalze();
    void Transform();
private:
    std::vector<Point> points;
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
