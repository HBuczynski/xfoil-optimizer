#include "optimizer/geometry.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using std::ofstream;
using std::ifstream;
using std::getline;

void Geometry::Load(std::string filename)
{
    ifstream file;
    file.open(filename,std::ios::in);
    if (file.is_open())
    {

        std::string name, line;
        if(!getline(file, name))
            throw std::out_of_range("File containing profile empty");

        points.clear();
        while(getline(file,line))
        {
            std::string::size_type sz;
            double x,y;
            //Can cause exception throws out of range
            x = std::stod(line,&sz);
            y = std::stod(line.substr(sz));
            points.push_back(Point(x,y));
        }
        file.close();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}
void Geometry::Save(std::string filename)
{
    ofstream file;
    file.open(filename,std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << filename << "\r\n";
        for(Point a : points)
        {
            file << "     "<< a.x << "    " << a.y << "\r\n";
        }
        file.close();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}
