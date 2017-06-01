#ifndef GEOMETRY_STRUCTURES_H
#define GEOMETRY_STRUCTURES_H

typedef std::uint8_t byte;

struct AirfoilCoefficients
{
    /** Parameters of medial-camber line function */
    //Param become larger: Overall shape becomeshigher
    //Param become smaller: Overall shape becomes lower
    double p_u;
    double p_l;
    //Param become larger: Forepart becomes lower significantly; Back part becomes lower slightly
    //Param become smaller: Forepart becomes higher significantly; Back part becomes higher slightly
    double a_u;
    double a_l;
    //Param become larger: Back part becomes lower significantly; Forepart part becomes lower slightly
    //Param become smaller: Back part becomes higher significantly; Forepart becomes higher slightly
    double b_u;
    double b_l;

    /** Parameters of thickness function */
    //Param become larger: Overall shape becomes thicker
    //Param become smaller: Overall shape becomes thinner
    double q_u;
    double q_l;
    //Param become larger: Forepart becomes thinner significantly; Back part becomes thinner slightly
    //Param become smaller: Forepart becomes thicker significantly; Back part becomes thicker slightly
    double c_u;
    double c_l;
    //Param become larger: Back part becomes thinner significantly; Forepart becomes thinner slightly
    //Param become smaller: Back part becomes thicker significantly; Forepart becomes thicker slightly
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

#endif // GEOMETRY_STRUCTURES_H
