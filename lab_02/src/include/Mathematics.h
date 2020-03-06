#ifndef __MATHEMTICS_H
#define __MATHEMTICS_H

#include "Interpolation.h"

class Mathematics
{
public:
    Mathematics(
        double L, double R, double U,
        double I, double tau, double t
    );
private:
    double _L;
    double _R;
    double _U;
    double _I;
    double _tau;
    double _t;
};

#endif // __MATHEMTICS_H
