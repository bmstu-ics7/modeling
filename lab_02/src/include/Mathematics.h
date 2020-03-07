#ifndef __MATHEMTICS_H
#define __MATHEMTICS_H

#include <cmath>
#include <vector>
#include "Interpolation.h"

class Mathematics
{
public:
    Mathematics(
        double Lk, double Rk, double Uc0,
        double I0, double tau, double tp
    );

    void process();

    std::vector<double> Ivec;
    std::vector<double> Rvec;
    std::vector<double> Uvec;
    std::vector<double> Tvec;
    std::vector<double> timevec;

private:
    void iteration();
    double f(double I, double Uc);
    double g(double I);
    double T(double z, double I);
    double integral(double z, double I);
    double trapezion(double a, double b, double I);
    double Rp(double I);

    const double _n = 1000;   // Количество разбиений интегрирования
    const double _R = 0.35;
    const double _Le = 12;
    const double _Ck = 0.000268;
    const double _Tw = 2000;
    const double _Lk;
    const double _Rk;
    const double _tau;
    const double _tp;
    double _Uc;
    double _I;
};

#endif // __MATHEMTICS_H
