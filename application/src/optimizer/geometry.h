#pragma once
#include <vector>
#include "xfoil/simulation_results.h"

class Point;
class Geometry
{
public:
    Geometry()
    {
    }
    Geometry(std::string filename)
    {
        Load(filename);
    }
    void Load(std::string filename);
    void Save(std::string filename);
    void Normalze();
    void Transform();
    const std::vector<Point>& GetPoints()
    {
        return points;
    }
    const SimResults& GetResults()
    {
        return *simResults_;
    }

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
inline bool operator==(const Point& lhs, const Point& rhs)
{
    double eps = 0.00000001;
    if(abs(lhs.x - rhs.x) < eps && abs(lhs.y - rhs.y) < eps)
        return true;
    return false;
}
