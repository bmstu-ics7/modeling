#include "Mathematics.h"
#include <cmath>

Mathematics::Mathematics(
    const double alpha0, const double alphaN, const double l,
    const double T0, const double R, const double Fmax, const double Tmax,
    const double nu,
    const bool needX, const bool needTau, const bool needXn,
    const bool needC, const bool needImpulse
) : _alpha0(alpha0), _alphaN(alphaN), _l(l),
    _T0(T0), _R(R), _Fmax(Fmax), _Tmax(Tmax),
    _nu(1.0 / nu)
{
    if (needX) {
        _onlyFirst = false;
        _epsRun = 1e-1;
        _epsIt = 1e-3;

        _tau = 0.1;
        double stepH[] = { 1 , 0.1 , 0.01, 0.001 };

        for (int i = 0; i < 4; ++i) {
            temp = QVector<QVector<double>>();
            _h = stepH[i];

            iterations();

            QVector<double> row;
            for (auto t : temp) {
                row.append(t[0]);
            }

            testH.append(row);
        }
    }

    if (needTau) {
        _epsRun = 1e-2;
        _epsIt = 1e-6;

        _h = 0.01;
        double stepTau[] = { 1, 0.1, 0.01, 0.001 };
        _onlyFirst = true;

        for (int i = 0; i < 4; ++i) {
            temp = QVector<QVector<double>>();
            _tau = stepTau[i];

            iterations();
            QVector<double> row;

            for (auto t : temp[1 / _tau - 1]) {
                row.append(t);
            }

            testTau.append(row);
        }
    }

    if (needXn) {
        _epsRun = 1e-2;
        _epsIt = 1e-6;
        _h = 0.01;
        _tau = _Tmax / 1000.0;
        _onlyFirst = false;
        iterations();
        testXn = temp;
    }

    if (needC) {
        _tau = _Tmax / 1000.0;
        _h = 0.01;

        _onlyFirst = false;
        double a[] = { 2.049, 5, 10, 25 };
        double b[] = { 0.000564, 0.001, 0.01, 0.1 };
        _epsRun = 1e-3;
        _epsIt = 1e-6;

        for (int i = 0; i < 4; ++i) {
            temp = QVector<QVector<double>>();
            _a2 = a[i];
            _b2 = b[i];

            iterations();

            QVector<double> row;
            for (auto t : temp) {
                row.append(t[0]);
            }

            testAB.append(row);
        }
    }

    if (needImpulse) {
        _onlyFirst = false;
        _impulse = true;
        _epsRun = 1e-1;
        _epsIt = 1e-4;
        _h = 0.01;
        _tau = _Tmax / 1000.0;

        temp = QVector<QVector<double>>();
        iterations();
        for (auto t : temp) {
            testImpulse.append(t[0]);
        }
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
    QVector<double> tZero;
    int n = int(_l / _h) + 1;
    for (int i = 0; i < n; ++i) {
        tZero.append(_T0);
    }

    temp.append(tZero);

    double t = _tau;

    do {
        QVector<double> prev;
        QVector<double> curr = temp.last();

        do {
            prev = curr;
            curr = runTrought(prev, t);
        } while (!endRunTrought(prev, curr));

        t += _tau;
        temp.append(curr);

        if (_onlyFirst && t >= 1)
            break;
    } while (!endIterations(t));
}

QVector<double> Mathematics::runTrought(const QVector<double> &prev, const double t)
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
        F(t) * _tau +
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
        _h / 8.0 * c1_2(prev.last(), -_tau) * prev[prev.count() - 2] + _h / 8.0 * c1_2(prev.last(), -_tau) * prev.last() +
        _T0 * _alphaN * _tau +
        (f(_l) + f1_2(_l, -_h)) * _tau * _h / 4.0;

    QVector<double> eps;
    eps.append(0);
    eps.append(-M0 / K0);

    QVector<double> eta;
    eta.append(0);
    eta.append(P0 / K0);

    int n = 1;
    for (double x = _h; x + _h < _l; x += _h, n += 1) {
        double epsN = eps.last();
        double etaN = eta.last();
        eps.append(D(prev[n]) / (B(prev[n], x) - A(prev[n]) * epsN));
        eta.append((F(prev[n], x) + A(prev[n]) * etaN) /
            (B(prev[n], x) - A(prev[n]) * epsN));
    }

    QVector<double> y(eps.count());
    y[y.count() - 1] = (PN - MN * eta.last()) / (KN + MN * eps.last());

    for (int i = y.count() - 2; i >= 0; --i) {
        y[i] = eps[i + 1] * y[i + 1] + eta[i + 1];
    }

    return y;
}

bool Mathematics::endIterations(const double t)
{
    if (_impulse) {
        return t > 300;
    }

    int last = temp.count() - 1;
    for (int i = 0; i < temp[last].count(); ++i) {
        if (std::fabs((temp[last][i] - temp[last - 1][i]) / temp[last][i]) > _epsIt)
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

    return max < _epsRun;
}

double Mathematics::F(const double t)
{
    if (_impulse) {
        double newT = std::round(std::fmod(t, _nu) * 100) / 100.0;
        if (_nu <= 0.01) newT = 10;
        return (_Fmax / _Tmax) * newT * std::exp(-(newT / _Tmax - 1));
    }

    return (_Fmax / _Tmax) * t * std::exp(-(t / _Tmax - 1));
}
