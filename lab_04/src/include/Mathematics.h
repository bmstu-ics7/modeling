#ifndef __MATHEMATICS_H
#define __MATHEMATICS_H

#include <QVector>

class Mathematics
{
public:
    Mathematics(
        const double a1, const double b1, const double c1, const double m1,
        const double a2, const double b2, const double c2, const double m2,
        const double alpha0, const double alphaN, const double l,
        const double T0, const double R, const double Ft
    );

public:
    QVector<QVector<double>> temp;
    const double _h = 0.01;
    const double _tau = 1;

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
    void iterations();
    bool endIterations();
    QVector<double> runTrought();
    bool endRunTrought(
        const QVector<double> &prev,
        const QVector<double> &current
    );

private:
    const double _eps = 1e-2;

    const double _a1;
    const double _b1;
    const double _c1;
    const double _m1;

    const double _a2;
    const double _b2;
    const double _c2;
    const double _m2;

    const double _alpha0;
    const double _alphaN;
    const double _l;
    const double _T0;
    const double _R;
    const double _Ft;
};

#endif // __MATHEMATICS_H
