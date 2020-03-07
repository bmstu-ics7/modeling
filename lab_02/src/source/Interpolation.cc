#include "Interpolation.h"

Point Interpolation::_tableIT[9] =
{
    { 0.5,   6700 },
    { 1,     6790 },
    { 5,     7150 },
    { 10,    7270 },
    { 50,    8010 },
    { 200,   9185 },
    { 400,   10010 },
    { 800,   11140 },
    { 1200,  12010 }
};

Point Interpolation::_tableIM[9] =
{
    { 0.5,   0.50 },
    { 1,     0.55 },
    { 5,     1.70 },
    { 10,    3.0 },
    { 50,    11.0 },
    { 200,   32.0 },
    { 400,   40.0 },
    { 800,   41.0 },
    { 1200,  39.0 }
};

Point Interpolation::_tableTSig[11] =
{
    { 4000,  0.031 },
    { 5000,  0.27 },
    { 6000,  2.05 },
    { 7000,  6.06 },
    { 8000,  12.0 },
    { 9000,  19.9 },
    { 10000, 29.6 },
    { 11000, 41.1 },
    { 12000, 54.1 },
    { 13000, 67.7 },
    { 14000, 81.5 },
};

double Interpolation::get(Point *table, double x, unsigned short int len)
{
    int index = -1;
    for (int i = 1; i < len; ++i) {
        if (x >= table[i - 1].x && x <= table[i].x) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        if (x <= table[0].x) return table[0].y;
        else return table[len - 1].y;
    }

    double x0 = table[index - 1].x;
    double y0 = table[index - 1].y;
    double x1 = table[index].x;
    double y1 = table[index].y;
    return y0 + ((y1 - y0) / (x1 - x0)) * (x - x0);
}

double Interpolation::getT(double I)
{
    return get(_tableIT, I, 9);
}

double Interpolation::getM(double I)
{
    return get(_tableIM, I, 9);
}

double Interpolation::getSig(double T)
{
    return get(_tableTSig, T, 11);
}
