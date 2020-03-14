#include "Mathematics.h"

Mathematics::Mathematics(
    double Lk, double Rk, double Uc0,
    double I0, double tau, double tp
) : _Lk(Lk), _Rk(Rk), _Uc(Uc0), _I(I0), _tau(tau), _tp(tp) { }

void Mathematics::process()
{
    for (double t = 0; t <= _tp; t += _tau) {
        Ivec.push_back(_I);
        Rvec.push_back(Rp(_I));
        Uvec.push_back(_Uc);
        Tvec.push_back(Interpolation::getT(_I));
        timevec.push_back(t);

        iteration();
    }
}

void Mathematics::iteration()
{
    double k1 = f(_I, _Uc);
    double m1 = g(_I);

    double k2 = f(_I + _tau * (k1 / 2.0), _Uc + _tau * (m1 / 2.0));
    double m2 = g(_I + _tau * (k1 / 2.0));

    double k3 = f(_I + _tau * (k2 / 2.0), _Uc + _tau * (m2 / 2.0));
    double m3 = g(_I + _tau * (k2 / 2.0));

    double k4 = f(_I + _tau * k3, _Uc + _tau * m3);
    double m4 = g(_I + _tau * k3);

    _I  += _tau * ((k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0);
    _Uc += _tau * ((m1 + 2.0 * m2 + 2.0 * m3 + m4) / 6.0);
}

double Mathematics::f(double I, double Uc)
{
    return (Uc - (_Rk + Rp(I)) * I) / _Lk;
}

double Mathematics::g(double I)
{
    return -I / _Ck;
}

double Mathematics::T(double z, double I)
{
    double T0 = Interpolation::getT(I);
    double m = Interpolation::getM(I);
    return T0 + (_Tw - T0) * std::pow(z, m);
}

double Mathematics::integral(double z, double I)
{
    return Interpolation::getSig(T(z, I)) * (z);
}

double Mathematics::trapezion(double a, double b, double I)
{
    double result = 0;
    double step = (b - a) / double(_n);
    for (double z = a; z < b; z += step) {
        result += integral(z, I);
    }
    return result;
}

double Mathematics::Rp(double I)
{
    I = std::abs(I);
    return _Le / (2.0 * M_PI * _R * _R * trapezion(0.0, 1.0, I));
    // return 0;
}
