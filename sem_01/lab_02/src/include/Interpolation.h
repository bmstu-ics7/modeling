#ifndef __INTERPOLATION_H
#define __INTERPOLATION_H

struct Point
{
    double x;
    double y;
};

class Interpolation
{
public:
    static double getT(double I);
    static double getM(double I);
    static double getSig(double T);

private:
    static double get(Point *table, double x, unsigned short int len);
    static Point _tableIT[9];
    static Point _tableIM[9];
    static Point _tableTSig[11];
};

#endif // __INTERPOLATION_H
