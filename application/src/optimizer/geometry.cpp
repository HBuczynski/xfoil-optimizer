#include "optimizer/geometry.h"
#include <math.h>

#include <QDebug>

using std::ofstream;
using std::ifstream;
using std::getline;

Geometry::Geometry()
{
    calculateCoefficients();
}

Geometry::Geometry(AirfoilCoefficients coeff)
{
    coefficients_ = coeff;
    this->calculateCordinateOfX();
    this->transform();
}

Geometry::Geometry(std::string filename)
{
    load(filename);
    calculateCoefficients();
}

void Geometry::load(std::string filename)
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
        this->calculateCoefficients();
    }
    else
    {
        throw std::invalid_argument("Invalid file path");
    }
}

//TODO make regression methods
void Geometry::calculateCoefficients()
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
    this->transform();
}

void Geometry::createNewGeometry(AirfoilCoefficients coeff)
{
    coefficients_ = coeff;
    //To do: calculateX and transform y
}

void Geometry::saveCoefficients(std::string filename)
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

void Geometry::loadFromCoefficients(std::string filename)
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
    //Repair - look up report!
    return false;
    //Alert this is because function generating airfoil is wrong//


    for(int i=0; i<lowerPoints_.size(); ++i)
    {
        if(upperPoints_[i].y <= lowerPoints_[lowerPoints_.size()-1-i].y)
            return true;
    }
    //Check for airfoil tip nose angle//
    double ang1, ang2;
    //std::cout<<"Anglert " <<lowerPoints_[1].y << "  "<<lowerPoints_[0].y<<std::endl;
    ang1 = atan2(upperPoints_[upperPoints_.size() - 2].y - upperPoints_[upperPoints_.size() - 1].y,
            upperPoints_[upperPoints_.size() - 2].x - upperPoints_[upperPoints_.size() - 1].x);
    ang2 = atan2(lowerPoints_[1].y - lowerPoints_[0].y,lowerPoints_[1].x - lowerPoints_[0].x);

    ang1 *= 180.0 /3.141592;
    ang2 *= 180.0 /3.141592;
    //Check for thickness inbalance//
    double maxY = upperPoints_[0].y, minY = lowerPoints_[0].y;
    for(int i=0; i<lowerPoints_.size(); ++i)
    {
        if(upperPoints_[i].y > maxY)
            maxY = upperPoints_[i].y;
        if(lowerPoints_[i].y < minY)
            minY = lowerPoints_[i].y;
    }
    double ratio = maxY / std::abs(minY);
    //Check max thickness//
    if(maxY-minY > 0.5)
        return true;


    //Checksymetry//
   // if(ratio > 4 || 1.0 / ratio > 4)
   //     return true;
    //Check leading edge pointiness//

  //  std::cout<<ang1<<" "<<ang2<<" "<<ang1-ang2<<std::endl;
   if((ang1- ang2)< 120.0)
        return true;
   //Lastly check for Trailing edge thickness//
   if(std::abs(lowerPoints_[upperPoints_.size() - 1].y - upperPoints_[0].y) > 0.03)
           return true;
 //   std::cout<<"Anglert " <<ang1<< "  "<<ang2<<std::endl;
    return false;
}

const SimResults &Geometry::getResults()
{
    return simResults_;
}
void Geometry::save(std::string filename)
{
    //Repair - look up report!
    AirfoilCoefficients saveCoeff = coefficients_;
    calculateCoefficients();
    transform();
    //Alert this is because function generating airfoil is wrong//
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
    coefficients_ = saveCoeff;
    transform();
}

void Geometry::transform()
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


    if(upperPoints_[lastElement].y == lowerPoints_[0].y)
    {
       upperPoints_[lastElement].y = (upperPoints_[lastElement-1].y)/2;
       lowerPoints_[0].y = (lowerPoints_[1].y)/2;
    }

    if(upperPoints_[0].y == lowerPoints_[lastElement].y)
    {
       upperPoints_[0].y = (upperPoints_[1].y)/2;
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

std::vector<Point> Geometry::getPoints()
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

