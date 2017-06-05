#ifndef GEOMETRY_STRUCTURES_H
#define GEOMETRY_STRUCTURES_H

typedef std::uint8_t byte;
#include <cmath>

/**
*	@file geometry_structures.h
*	@brief This header file contains all required structures to represent geometry's coefficients.
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

/**
*	@struct AirfoilCoefficients
*   Param become larger: Overall shape becomeshigher
*   Param become smaller: Overall shape becomes lower
*   @var AirfoilCoefficients::p_u
*   Param become larger: Overall shape becomeshigher
*   Param become smaller: Overall shape becomes lower
*   @var AirfoilCoefficients::p_l
*   Param become larger: Forepart becomes lower significantly; Back part becomes lower slightly
*   Param become smaller: Forepart becomes higher significantly; Back part becomes higher slightly
*   @var AirfoilCoefficients::a_u
*   Param become larger: Forepart becomes lower significantly; Back part becomes lower slightly
*   Param become smaller: Forepart becomes higher significantly; Back part becomes higher slightly
*   @var AirfoilCoefficients::a_l
*   Param become larger: Back part becomes lower significantly; Forepart part becomes lower slightly
*   Param become smaller: Back part becomes higher significantly; Forepart becomes higher slightly
*   @var AirfoilCoefficients::b_u
*   Param become larger: Back part becomes lower significantly; Forepart part becomes lower slightly
*   Param become smaller: Back part becomes higher significantly; Forepart becomes higher slightly
*   @var AirfoilCoefficients::b_l
*   Param become larger: Overall shape becomes thicker
*   Param become smaller: Overall shape becomes thinner
*   @var AirfoilCoefficients::q_u
*   Param become larger: Overall shape becomes thicker
*   Param become smaller: Overall shape becomes thinner
*   @var AirfoilCoefficients::q_l
*   Param become larger: Forepart becomes thinner significantly; Back part becomes thinner slightly
*   Param become smaller: Forepart becomes thicker significantly; Back part becomes thicker slightly
*   @var AirfoilCoefficients::c_u
*   Param become larger: Forepart becomes thinner significantly; Back part becomes thinner slightly
*   Param become smaller: Forepart becomes thicker significantly; Back part becomes thicker slightly
*   @var AirfoilCoefficients::c_l
*   Param become larger: Back part becomes thinner significantly; Forepart becomes thinner slightly
*   Param become smaller: Back part becomes thicker significantly; Forepart becomes thicker slightly
*   @var AirfoilCoefficients::d_u
*   Param become larger: Back part becomes thinner significantly; Forepart becomes thinner slightly
*   Param become smaller: Back part becomes thicker significantly; Forepart becomes thicker slightly
*   @var AirfoilCoefficients::d_l
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/

struct AirfoilCoefficients
{
    /** Parameters of medial-camber line function */
    double p_u;
    double p_l;
    double a_u;
    double a_l;
    double b_u;
    double b_l;

    /** Parameters of thickness function */
    double q_u;
    double q_l;
    double c_u;
    double c_l;
    double d_u;
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

    AirfoilCoefficients &operator =(const AirfoilCoefficients &data)
    {
        p_u = data.p_u;
        q_u = data.q_u;
        a_u = data.a_u;
        b_u = data.b_u;
        c_u = data.c_u;
        d_u = data.d_u;
        p_l = data.p_l;
        q_l = data.q_l;
        a_l = data.a_l;
        b_l = data.b_l;
        c_l = data.c_l;
        d_l = data.d_l;

        return *this;
    }
};

/**
*	@struct BinaryAirfoilCoefficients
*   Param become larger: Overall shape becomeshigher
*   Param become smaller: Overall shape becomes lower
*   @var BinaryAirfoilCoefficients::p_u
*   Param become larger: Overall shape becomeshigher
*   Param become smaller: Overall shape becomes lower
*   @var BinaryAirfoilCoefficients::p_l
*   Param become larger: Forepart becomes lower significantly; Back part becomes lower slightly
*   Param become smaller: Forepart becomes higher significantly; Back part becomes higher slightly
*   @var BinaryAirfoilCoefficients::a_u
*   Param become larger: Forepart becomes lower significantly; Back part becomes lower slightly
*   Param become smaller: Forepart becomes higher significantly; Back part becomes higher slightly
*   @var BinaryAirfoilCoefficients::a_l
*   Param become larger: Back part becomes lower significantly; Forepart part becomes lower slightly
*   Param become smaller: Back part becomes higher significantly; Forepart becomes higher slightly
*   @var BinaryAirfoilCoefficients::b_u
*   Param become larger: Back part becomes lower significantly; Forepart part becomes lower slightly
*   Param become smaller: Back part becomes higher significantly; Forepart becomes higher slightly
*   @var BinaryAirfoilCoefficients::b_l
*   Param become larger: Overall shape becomes thicker
*   Param become smaller: Overall shape becomes thinner
*   @var BinaryAirfoilCoefficients::q_u
*   Param become larger: Overall shape becomes thicker
*   Param become smaller: Overall shape becomes thinner
*   @var BinaryAirfoilCoefficients::q_l
*   Param become larger: Forepart becomes thinner significantly; Back part becomes thinner slightly
*   Param become smaller: Forepart becomes thicker significantly; Back part becomes thicker slightly
*   @var BinaryAirfoilCoefficients::c_u
*   Param become larger: Forepart becomes thinner significantly; Back part becomes thinner slightly
*   Param become smaller: Forepart becomes thicker significantly; Back part becomes thicker slightly
*   @var BinaryAirfoilCoefficients::c_l
*   Param become larger: Back part becomes thinner significantly; Forepart becomes thinner slightly
*   Param become smaller: Back part becomes thicker significantly; Forepart becomes thicker slightly
*   @var BinaryAirfoilCoefficients::d_u
*   Param become larger: Back part becomes thinner significantly; Forepart becomes thinner slightly
*   Param become smaller: Back part becomes thicker significantly; Forepart becomes thicker slightly
*   @var BinaryAirfoilCoefficients::d_l
*	@author Jakub Polaczek & Hubert Buczyński
*	@date 05/06/2017
*/
#pragma pack(push,1)
struct BinaryAirfoilCoefficients
{
    byte p_u;
    byte p_l;
    byte a_u;
    byte a_l;
    byte b_u;
    byte b_l;

    byte q_u;
    byte q_l;
    byte c_u;
    byte c_l;
    byte d_u;
    byte d_l;

    BinaryAirfoilCoefficients() :   p_u(0),
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

    BinaryAirfoilCoefficients &operator =(const BinaryAirfoilCoefficients &data)
    {
        p_u = data.p_u;
        q_u = data.q_u;
        a_u = data.a_u;
        b_u = data.b_u;
        c_u = data.c_u;
        d_u = data.d_u;
        p_l = data.p_l;
        q_l = data.q_l;
        a_l = data.a_l;
        b_l = data.b_l;
        c_l = data.c_l;
        d_l = data.d_l;

        return *this;
    }
};
#pragma pack(pop)

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
    if(std::abs(lhs.x - rhs.x) < eps && std::abs(lhs.y - rhs.y) < eps)
        return true;
    return false;
}

#endif // GEOMETRY_STRUCTURES_H
