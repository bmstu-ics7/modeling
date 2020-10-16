#ifndef __MATHEMATICS_H
#define __MATHEMATICS_H

#include <QVector>

class Mathematics
{
public:
    Mathematics(
        const double alpha0, const double alphaN, const double l,
        const double T0, const double R, const double Fmax, const double Tmax,
        const double nu,
        const bool needX, const bool needTau, const bool needXn,
        const bool needC, const bool needImpulse
    );
    void iterations();

public:
    double _h;
    double _tau;

    QVector<QVector<double>> temp;

    QVector<QVector<double>> testH;
    QVector<QVector<double>> testTau;

    QVector<QVector<double>> testXn;
    QVector<QVector<double>> testAB;
    QVector<double> testImpulse;

private:
    double alpha(const double x);
    double k(const double T);
    double c(const double T);
    double p(const double x);
    double f(const double x);
    double chi1_2(const double T, const double tau);
    double A(const double T);
    double B(const double T, const double x);
    double D(const double T);
    double F(const double T, const double x);
    double c1_2(const double T, const double tau);
    double p1_2(const double x, const double h);
    double f1_2(const double x, const double h);
    bool endIterations(const double t);
    QVector<double> runTrought(const QVector<double> &prev, const double t);
    bool endRunTrought(
        const QVector<double> &prev,
        const QVector<double> &current
    );
    double F(const double t);

private:
    const double _eps = 1e-4;
    double _epsRun;
    double _epsIt;

    const double _a1 = 0.0134;
    const double _b1 = 1;
    const double _c1 = 0.000435;
    const double _m1 = 1;

    double _a2 = 2.049;
    double _b2 = 0.000563;
    const double _c2 = 52800;
    const double _m2 = 1;

    const double _alpha0;
    const double _alphaN;
    const double _l;
    const double _T0;
    const double _R;

    double _Fmax;
    double _Tmax;

    bool _onlyFirst = false;
    bool _impulse = false;

    const double _nu;
};

#endif // __MATHEMATICS_H
