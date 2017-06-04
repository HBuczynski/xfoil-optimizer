#include "optimizer/geometry.h"
#include <math.h>

#include <QDebug>

using std::ofstream;
using std::ifstream;
using std::getline;

Geometry::Geometry()
{
    CalculateCoefficients();
}

Geometry::Geometry(AirfoilCoefficients coeff)
{
    coefficients_ = coeff;
    this->calculateCordinateOfX();
    this->Transform();
}

Geometry::Geometry(std::string filename)
{
    Load(filename);
    CalculateCoefficients();
}

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
        this->CalculateCoefficients();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}

//TODO make regression methods
void Geometry::CalculateCoefficients()
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
//    this->SaveCoefficients();
    this->calculateCordinateOfX();
    this->Transform();
}

void Geometry::createNewGeometry(AirfoilCoefficients coeff)
{
    coefficients_ = coeff;
    //To do: calculateX and transform y
}

void Geometry::SaveCoefficients(std::string filename)
{
    ofstream file;
    file.open(filename,std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << "p_u" << "\t" << coefficients_.p_u << std::endl;
        file << "q_u" << "\t" << coefficients_.q_u << std::endl;
        file << "a_u" << "\t" << coefficients_.a_u << std::endl;
        file << "b_u" << "\t" << coefficients_.b_u << std::endl;
        file << "c_u" << "\t" << coefficients_.c_u << std::endl;
        file << "d_u" << "\t" << coefficients_.d_u << std::endl;
        file << "p_l" << "\t" << coefficients_.p_l << std::endl;
        file << "q_l" << "\t" << coefficients_.q_l << std::endl;
        file << "a_l" << "\t" << coefficients_.a_l << std::endl;
        file << "b_l" << "\t" << coefficients_.b_l << std::endl;
        file << "c_l" << "\t" << coefficients_.c_l << std::endl;
        file << "d_l" << "\t" << coefficients_.d_l << std::endl;
        file.close();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}

void Geometry::LoadFromCoefficients(std::string filename)
{
    ifstream file;
    file.open(filename,std::ios::in);
    if (file.is_open())
    {
        std::string name, line;
        if(!getline(file, name, '\t'))
            throw std::out_of_range("File containing coefficients empty");

        std::string::size_type sz;
        getline(file,line);
        coefficients_.p_u = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.q_u = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.a_u = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.b_u = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.c_u = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.d_u = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.p_l = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.q_l = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.a_l = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.b_l = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.c_l = std::stod(line,&sz);
        getline(file,line, '\t');
        getline(file,line);
        coefficients_.d_l = std::stod(line,&sz);
        file.close();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}

void Geometry::calculateCordinateOfX()
{
    if(vectorX_.size() > 0)
        return;
    else
    {
        for(double i=0; i< distanceFromEdgeOfAttack; i+=pointsDensity)
            vectorX_.push_back(i);

        double airfoilDensity = (1-distanceFromEdgeOfAttack)/(pointsCount -1 - distanceFromEdgeOfAttack/pointsDensity);

        for(double i=distanceFromEdgeOfAttack; i <1; i+=airfoilDensity)
            vectorX_.push_back(i);
        if(*(--vectorX_.end()) < 1)
            *(--vectorX_.end()) = 1;
    }
}

bool Geometry::isProfileCrossed()
{
    for(int i=0; i<lowerPoints_.size(); --i)
    {
        if(upperPoints_[i].y <= lowerPoints_[lowerPoints_.size()-1-i].y)
            return true;
    }
    return false;
}
void Geometry::Save(std::string filename)
{
    ofstream file;
    file.open(filename,std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << filename << std::endl;
        for(Point a: upperPoints_)
        {
            file << "     "<< a.x << "    " << a.y << std::endl;
        }

        for(Point a : lowerPoints_)
        {
            file << "     "<< a.x << "    " << a.y << std::endl;
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
    upperPoints_.clear();
    lowerPoints_.clear();
    //Calculate points based on new coefficients
    for(int i=vectorX_.size()-1; i>=0; --i)
    {
        upperPoints_.push_back(Point(vectorX_[i], (coefficients_.p_u*pow(vectorX_[i], coefficients_.a_u)*pow((1-vectorX_[i]), coefficients_.b_u)+
                           coefficients_.q_u*pow(vectorX_[i], coefficients_.c_u)*pow((1-vectorX_[i]), coefficients_.d_u))));
    }

    for(int i=0; i<vectorX_.size(); ++i)
    {
        lowerPoints_.push_back(Point(vectorX_[i], (coefficients_.p_l*pow(vectorX_[i], coefficients_.a_l)*pow((1-vectorX_[i]), coefficients_.b_l)-
                            coefficients_.q_l*pow(vectorX_[i], coefficients_.c_l)*pow((1-vectorX_[i]), coefficients_.d_l))));
    }

    size_t lastElement = upperPoints_.size() - 1;

    if(upperPoints_[lastElement].y == lowerPoints_[lastElement].y)
    {
       upperPoints_[lastElement].y = (upperPoints_[lastElement-1].y)/2;
       lowerPoints_[lastElement].y = (lowerPoints_[lastElement-1].y)/2;
    }
}

void Geometry::regressionAlgorithm()
{

}

const AirfoilCoefficients &Geometry::getAifroilCoefficients()
{
    return this->coefficients_;
}

std::vector<Point> Geometry::GetPoints()
{
    std::vector<Point> points;

    for(Point a: upperPoints_)
        points.push_back(a);

    for(Point a : lowerPoints_)
        points.push_back(a);
    return points;
}

const int &Geometry::getPointsCount()
{
    return pointsCount;
}

