#ifndef MATHPHY_H
#define MATHPHY_H

constexpr double cpow(double base, int exp)
{
    if( exp < 0 )
    {
        base = 1/base;
        exp = -exp;
    }
    if( exp == 1 )
    {
        return base;
    }
    return base*cpow(base,exp-1);
}

constexpr double mu = 3.986005*cpow(10.0,14);
constexpr double we = 7.292115*cpow(10.0,-5);


#endif // MATHPHY_H
