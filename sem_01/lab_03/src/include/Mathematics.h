#ifndef __MATHEMATICS_H
#define __MATHEMATICS_H

#include <QVector>

class Mathematics
{
public:
    Mathematics(const double k0, const double kn, const double a0, const double an, const double F0, const bool ax3);

public:
    QVector<double> X;
    QVector<double> Y;

private:
    double k(const double x);
    double alpha(const double x);
    double p(const double x);
    double f(const double x);

    void findCoeff();

    double A(const double x);
    double B(const double x);
    double C(const double x);
    double D(const double x);

    void findResult();

private:
    const double _multiAlpha;
    const double _k0;
    const double _kn;
    const double _alpha0;
    const double _alphaN;
    const double _F0;

    const double _l = 10;
    const double _T0 = 300;
    const double _R = 0.5;

    const double _h = 0.1;

    const double _a;
    const double _b;
    const double _c;
    const double _d;

    double _K0;
    double _KN;
    double _M0;
    double _MN;
    double _P0;
    double _PN;

    QVector<double> _eps;
    QVector<double> _eta;
};

#endif // __MATHEMATICS_H
