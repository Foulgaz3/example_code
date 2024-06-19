
#include "point.h"
#include <math.h>

double point_magnitude(Point P) {
    double r2 = P.X*P.X + P.Y*P.Y;
    return sqrt(r2);
}

Point point_add(Point P1, Point P2) {
    Point result;
    result.X = P1.X + P2.X;
    result.Y = P1.Y + P2.Y;
    return result;
}

Point point_sub(Point P1, Point P2) {
    Point result;
    result.X = P1.X - P2.X;
    result.Y = P1.Y - P2.Y;
    return result;
}

Point point_scale(Point P, double val) {
    Point result;
    result.X = P.X * val;
    result.Y = P.Y * val;
    return result;
}

double point_dot(Point P1, Point P2) {
    return P1.X * P2.X + P1.Y * P2.Y;
}
