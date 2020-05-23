#include "Mathematics.h"
#include <cmath>
#include <QDebug>

Mathematics::Mathematics(
    const double a1, const double b1, const double c1, const double m1,
    const double a2, const double b2, const double c2, const double m2,
    const double alpha0, const double alphaN, const double l,
    const double T0, const double R, const double Ft
) : _a1(a1), _b1(b1), _c1(c1), _m1(m1),
    _a2(a2), _b2(b2), _c2(c2), _m2(m2),
    _alpha0(alpha0), _alphaN(alphaN), _l(l),
    _T0(T0), _R(R), _Ft(Ft)
{
    iterations();
}

double Mathematics::alpha(const double x)
{
    double d = (_alphaN * _l) / (_alphaN - _alpha0);
    double c = -_alpha0 * d;
    return c / (x - d);
}

double Mathematics::k(const double T)
{
    return _a1 * (_b1 + _c1 * std::pow(T, _m1));
}

double Mathematics::c(const double T)
{
    return _a2 + _b2 * std::pow(T, _m2) - _c2 / (T * T);
}

double Mathematics::p(const double x)
{
    return (2.0 / _R) * alpha(x);
}

double Mathematics::f(const double x)
{
    return (2.0 * _T0 / _R) * alpha(x);
}

double Mathematics::chi1_2(const double T, const double tau)
{
    return (k(T) + k(T + tau)) / 2.0;
}

double Mathematics::A(const double T)
{
    return chi1_2(T, -_tau) * _tau / _h;
}

double Mathematics::B(const double T, const double x)
{
    return A(T) + D(T) + c(T) * _h + p(x) * _h * _tau;
}

double Mathematics::D(const double T)
{
    return chi1_2(T, _tau) * _tau / _h;
}

double Mathematics::F(const double T, const double x)
{
    return f(x) * _h * _tau + c(T) * T * _h;
}

double Mathematics::c1_2(const double T, const double tau)
{
    return (c(T) + c(T + tau)) / 2.0;
}

double Mathematics::p1_2(const double x, const double h)
{
    return (p(x) + p(x + h)) / 2.0;
}

double Mathematics::f1_2(const double x, const double h)
{
    return (f(x) + f(x + h)) / 2.0;
}

void Mathematics::iterations()
{
    QVector<double> tZero;
    int n = int(_l / _h) + 1;
    for (int i = 0; i < n; ++i) {
        tZero.append(_T0);
    }

    temp.append(tZero);

    do {
        QVector<double> prev;
        QVector<double> curr = temp.last();

        do {
            prev = curr;
            curr = runTrought(prev);
        } while (!endRunTrought(prev, curr));

        temp.append(curr);
    } while (!endIterations());
}

QVector<double> Mathematics::runTrought(const QVector<double> &prev)
{
    const double K0 = _h / 8.0 * c1_2(prev[0], _tau) +
        _h / 4.0 * c(prev[0]) + chi1_2(prev[0], _tau) *
        _tau / _h + _tau * _h / 8.0 * p1_2(0, _h) +
        _tau * _h / 4.0 * p(0);
    const double M0 = _h / 8.0 * c1_2(prev[0], _tau) -
        chi1_2(prev[0], _tau) * _tau / _h +
        _tau * _h / 8.0 * p1_2(0, _h);
    const double P0 = _h / 8.0 * c1_2(prev[0], _tau) * (prev[0] + prev[1]) +
        _h / 4.0 * c(prev[0]) * prev[0] +
        _Ft * _tau +
        _tau * _h / 4.0 * (f1_2(0, _h) + f(0));

    const double KN = _h / 4.0 * c(prev.last()) +
        _h / 8.0 * c1_2(prev.last(), -_tau) +
        _alphaN * _tau +
        chi1_2(prev.last(), -_tau) * _tau / _h +
        p(_l) * _tau * _h / 4.0 +
        p1_2(_l, -_h) * _tau * _h / 8.0;
    const double MN = _h / 8.0 * c1_2(prev.last(), -_tau) -
        chi1_2(prev.last(), -_tau) * _tau / _h +
        p1_2(_l, -_h) * _tau * _h / 8.0;
    const double PN = _h / 4.0 * c(prev.last()) * prev.last() +
        _h / 8.0 * c1_2(prev.last(), -_tau) * prev[prev.count() - 2] +
        _h / 8.0 * c1_2(prev.last(), -_tau) * prev.last() +
        _T0 * _alphaN * _tau +
        (f(_l) + f1_2(_l, -_h)) * _tau * _h / 4.0;

    QVector<double> eps;
    eps.append(-M0 / K0);

    QVector<double> eta;
    eta.append(P0 / K0);

    for (double x = _h; x + _h < _l; x += _h) {
        double epsN = eps.last();
        double etaN = eta.last();
        eps.append(D(prev.last()) / (B(prev.last(), x) - A(prev.last()) * epsN));
        eta.append((F(prev.last(), x) + A(prev.last()) * etaN) /
            (B(prev.last(), x) - A(prev.last()) * epsN));
    }

    QVector<double> t(eps.count());
    t[t.count() - 1] = (PN - MN * eta.last()) / (KN + MN * eps.last());

    for (int i = t.count() - 2; i >= 0; --i) {
        t[i] = eps[i + 1] * t[i + 1] + eta[i + 1];
    }

    return t;
}

bool Mathematics::endIterations()
{
    int last = temp.count() - 1;
    for (int i = 0; i < temp[last].count(); ++i) {
        if (std::fabs((temp[last][i] - temp[last - 1][i]) / temp[last][i]) > _eps)
            return false;
    }

    return true;
}

bool Mathematics::endRunTrought(
    const QVector<double> &prev,
    const QVector<double> &current
)
{
    double max = std::fabs((current[0] - prev[0]) / current[0]);

    for (int i = 1; i < std::min(current.count(), prev.count()); ++i) {
        double e = std::fabs((current[i] - prev[i]) / current[i]);

        if (e > max)
            max = e;
    }

    return max < 1;
}
