#include "optimizer/geometry.h"

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

        upperPoints_.clear();
        lowerPoints_.clear();

        while(getline(file,line))
        {
            std::string::size_type sz;
            double x,y;
            //Can cause exception throws out of range
            x = std::stod(line,&sz);
            y = std::stod(line.substr(sz));

            if(y >= 0)
                upperPoints_.push_back(Point(x,y));
            else
                lowerPoints_.push_back(Point(x,y));
        }
        file.close();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}

void Geometry::InitializeCoefficients()
{
    coefficients_.p_u = 0.2;
    coefficients_.q_u = 0.295;
    coefficients_.a_u = 1.1;
    coefficients_.b_u = 2.3;
    coefficients_.c_u = 0.58;
    coefficients_.d_u = 1.03;

    coefficients_.p_l = 0.26;
    coefficients_.q_l = 0.85;
    coefficients_.a_l = 0.75;
    coefficients_.b_l = 0.9;
    coefficients_.c_l = 0.73;
    coefficients_.d_l = 1.6;
}

void Geometry::InitializeVectorX()
{
    double number = 0;
    double increaseNumber = 1.0/pointsNumber;

    for(int i=0; i < pointsNumber; ++i)
    {
        vectorX_[i] = number;
        number = number + increaseNumber;
    }

}
void Geometry::Save(std::string filename)
{
    ofstream file;
    file.open(filename,std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << filename << "\r\n";
        for(Point a : upperPoints_)
        {
            file << "     "<< a.x << "    " << a.y << "\r\n";
        }

        for(Point a : lowerPoints_)
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

void Geometry::Transform()
{
    //Calculate points based on new coefficients
    //Musimy wcześniej zdefiniować długość wektora x, tutaj tylko modyfikujemy y

    for(int i=0; i<upperPoints_.size(); ++i)
    {
        upperPoints_[i].y = coefficients_.p_u*pow(vectorX_[i], coefficients_.a_u)*pow((1-vectorX_[i]), coefficients_.b_u)+
                            coefficients_.q_u*pow(vectorX_[i], coefficients_.c_u)*pow((1-vectorX_[i]), coefficients_.d_u);
    }

    for(int i=0; i<lowerPoints_.size(); ++i)
    {
        lowerPoints_[i].y = coefficients_.p_l*pow(vectorX_[i], coefficients_.a_l)*pow((1-vectorX_[i]), coefficients_.b_l)+
                            coefficients_.q_l*pow(vectorX_[i], coefficients_.c_l)*pow((1-vectorX_[i]), coefficients_.d_l);
    }

}

const std::vector<Point> Geometry::GetPoints()
{
    std::vector<Point> points;

    for(Point a : upperPoints_)
        points.push_back(a);

    for(Point a : lowerPoints_)
        points.push_back(a);

    return points;
}
