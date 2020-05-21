#include "Mathematics.h"

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
}
