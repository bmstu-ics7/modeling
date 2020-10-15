#include "Mathematics.h"
#include <cmath>

Mathematics::Mathematics(
    const double alpha0, const double alphaN, const double l,
    const double T0, const double R, const double Ft,
    const bool again, const bool another
) : _alpha0(alpha0), _alphaN(alphaN), _l(l),
    _T0(T0), _R(R), _Ft(Ft),
    _again(again), _anotherStart(another)
{
    if (_anotherStart) {
        _Ft = 0;
    }

    iterations();

    if (_again) {
        _Ft = 0;
        _secondRun = true;
        iterations();
    }
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
    if (!_secondRun) {
        QVector<double> tZero;
        int n = int(_l / _h) + 1;
        for (int i = 0; i < n; ++i) {
            if (_anotherStart) {
                tZero.append(1000);
            } else {
                tZero.append(_T0);
            }
        }

        temp.append(tZero);
    }

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

    int n = 1;
    for (double x = _h; x + _h < _l; x += _h, n += 1) {
        double epsN = eps.last();
        double etaN = eta.last();
        eps.append(D(prev[n]) / (B(prev[n], x) - A(prev[n]) * epsN));
        eta.append((F(prev[n], x) + A(prev[n]) * etaN) /
            (B(prev[n], x) - A(prev[n]) * epsN));
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
