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

private:
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
