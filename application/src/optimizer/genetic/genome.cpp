#include "optimizer/genetic/genome.h"
Genome::Genome(AirfoilCoefficients coeff) :
                                                    rng(std::random_device()()),
                                                    bytedist(0,255),
                                                    minCoeffRange_(0.0),
                                                    maxCoeffRange_(5.0),
                                                    geom_(nullptr)
{

    std::cout<<"Constructor of genome"<<std::endl<<std::flush;
    Set(coeff);

}
uint8_t Genome::getRandomByte()
{
    return (uint8_t)bytedist(rng);
}

Genome::Genome(unsigned char *array) :
                                                    rng(std::random_device()()),
                                                    bytedist(0,255),
                                                    minCoeffRange_(0.0),
                                                    maxCoeffRange_(5.0),
                                                    geom_(nullptr)
{

    Set(array);
}

Genome::~Genome()
{
    if(geom_ != nullptr)
        delete geom_;
}

void Genome::Set(AirfoilCoefficients &coefficients)
{
    BinaryAirfoilCoefficients binaryCoefficients;
    binaryCoefficients.a_l = convertTobyte(coefficients.a_l);
    binaryCoefficients.a_u = convertTobyte(coefficients.a_u);
    binaryCoefficients.b_l = convertTobyte(coefficients.b_l);
    binaryCoefficients.b_u = convertTobyte(coefficients.b_u);
    binaryCoefficients.c_l = convertTobyte(coefficients.c_l);
    binaryCoefficients.c_u = convertTobyte(coefficients.c_u);
    binaryCoefficients.d_l = convertTobyte(coefficients.d_l);
    binaryCoefficients.d_u = convertTobyte(coefficients.d_u);
    binaryCoefficients.p_l = convertTobyte(coefficients.p_l);
    binaryCoefficients.p_u = convertTobyte(coefficients.p_u);
    binaryCoefficients.q_l = convertTobyte(coefficients.q_l);
    binaryCoefficients.q_u = convertTobyte(coefficients.q_u);
    Set(binaryCoefficients);
}
AirfoilCoefficients Genome::getCoefficients()
{
    AirfoilCoefficients coeff;
    coeff.a_l = convertTodouble(binaryCoefficients_.a_l);
    coeff.a_u = convertTodouble(binaryCoefficients_.a_u);
    coeff.b_l = convertTodouble(binaryCoefficients_.b_l);
    coeff.b_u = convertTodouble(binaryCoefficients_.b_u);
    coeff.c_l = convertTodouble(binaryCoefficients_.c_l);
    coeff.c_u = convertTodouble(binaryCoefficients_.c_u);
    coeff.d_l = convertTodouble(binaryCoefficients_.d_l);
    coeff.d_u = convertTodouble(binaryCoefficients_.d_u);
    coeff.p_l = convertTodouble(binaryCoefficients_.p_l);
    coeff.p_u = convertTodouble(binaryCoefficients_.p_u);
    coeff.q_l = convertTodouble(binaryCoefficients_.q_l);
    coeff.q_u = convertTodouble(binaryCoefficients_.q_u);
    return coeff;
}

uint8_t Genome::convertTobyte(double val)
{
    double scale = 255.0 / (maxCoeffRange_ - minCoeffRange_);
    if(val > maxCoeffRange_)
        val = maxCoeffRange_;
    val -= minCoeffRange_;
    val *= scale;
    return (uint8_t) std::round(val);
}
double Genome::convertTodouble(uint8_t val)
{
    double scale = (maxCoeffRange_ - minCoeffRange_) / 255.0;
    double vald = (double) val;
    vald *= scale;
    return vald;
}
void Genome::Randomize()
{
    uint8_t *array = getCoefficientsArray();
    for(int i = 0; i < sizeof(BinaryAirfoilCoefficients); ++i)
            array[i] = getRandomByte();

}

void Genome::setFitness(double value)
{
    fitness_ = value;
}

Geometry *Genome::getGeometry()
{
    return geom_;
}

double &Genome::getFitness()
{
    return fitness_;
}

void Genome::Set(BinaryAirfoilCoefficients &airfoilCoefficients)
{
    Set(reinterpret_cast<uint8_t*>(&airfoilCoefficients));
}

void Genome::Set(unsigned char *array)
{
    memcpy(getCoefficientsArray(),array,sizeof(BinaryAirfoilCoefficients));
    AirfoilCoefficients coeff = getCoefficients();//We can now get them as they were copied//
    if(geom_ != nullptr)
        delete geom_; //Reload gemetry
    geom_ = new Geometry(coeff);
}

unsigned char *Genome::getCoefficientsArray()
{
    return reinterpret_cast<uint8_t*>(&binaryCoefficients_);
}
