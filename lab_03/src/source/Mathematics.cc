#include "Mathematics.h"

Mathematics::Mathematics(
    const double k0,
    const double kn,
    const double a0,
    const double an,
    const double F0,
    const bool ax3
)
    : _multiAlpha(ax3 ? 3.0 : 1.0 ),
    _k0(k0), _kn(kn), _alpha0(a0), _alphaN(an), _F0(F0),
    _a((_k0 * _kn * _l) / (_k0 - _kn)),
    _b((_kn * _l) / (_kn - _k0)),
    _c((_alpha0 * _alphaN * _l) / (_alpha0 - _alphaN)),
    _d((_alphaN * _l) / (_alphaN - _alpha0))
{
    double x1_2 = (2 * k(0) * k(_h)) / (k(0) + k(_h));
    double p0 = p(0);
    double p1_2 = (p0 + p(_h)) / 2.0;
    double f0 = f(0);
    double f1_2 = (f0 + f(_h)) / 2.0;

    _K0 = x1_2 + (_h * _h / 8.0) * p1_2 + (_h * _h / 4.0) * p0;
    _M0 = -x1_2 + (_h * _h / 8.0) * p1_2;
    _P0 = _h * _F0 + (_h * _h / 4.0) * (f1_2 + f0);

    double xN1_2 = (2 * k(_l) * k(_l - _h)) / (k(_l) + k(_l - _h));
    double alphaN = alpha(_l);
    double pN = p(_l);
    double pN1_2 = (pN + p(_l - _h)) / 2.0;
    double fN = f(_l);
    double fN1_2 = (fN + f(_l - _h)) / 2.0;

    _KN = -(xN1_2 / _h) - alphaN - (pN / 4.0) * _h - (pN1_2 / 8.0) * _h;
    _MN = (xN1_2 / _h) - (pN1_2 / 8.0 * _h);
    _PN = -alphaN * _T0 - ((fN1_2 + fN) / 4.0) * _h;

    findCoeff();
    findResult();
}

double Mathematics::k(const double x)
{
    return _a / (x - _b);
}

double Mathematics::alpha(const double x)
{
    return _multiAlpha * (_c / (x - _d));
}

double Mathematics::p(const double x)
{
    return (2 * alpha(x)) / _R;
}

double Mathematics::f(const double x)
{
    return (2 * _T0 * alpha(x)) / _R;
}

void Mathematics::findCoeff()
{
    _eps.append(-_M0 / _K0);
    _eta.append(_P0 / _K0);

    for (double x = _h; x <= _l; x += _h) {
        double epsLast = _eps.last();
        double etaLast = _eta.last();
        _eps.append(C(x) / (B(x) - A(x) * epsLast));
        _eta.append((D(x) + A(x) * etaLast) / (B(x) - A(x) * epsLast));
    }
}

double Mathematics::A(const double x)
{
    double kn = k(x);
    double kn1 = k(x - _h);
    return ((2 * kn * kn1) / (kn + kn1)) / _h;
}

double Mathematics::B(const double x)
{
    return A(x) + C(x) + p(x) * _h;
}

double Mathematics::C(const double x)
{
    double kn = k(x);
    double kn1 = k(x + _h);
    return ((2 * kn * kn1) / (kn + kn1)) / _h;
}

double Mathematics::D(const double x)
{
    return f(x) * _h;
}

void Mathematics::findResult()
{
    X.append(_l);
    Y.append((_PN - _MN * _eta.last()) / (_KN + _MN * _eps.last()));

    for (int i = _eta.length() - 2; i >= 0; --i) {
        X.append(i * _h);
        Y.append(_eps[i + 1] * Y.last() + _eta[i + 1]);
    }
}
