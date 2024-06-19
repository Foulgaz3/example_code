#ifndef POINT_H
#define POINT_H

typedef struct Point {
    double X;
    double Y;
} Point;

double point_magnitude(Point P);

Point point_add(Point P1, Point P2);

Point point_sub(Point P1, Point P2);

Point point_scale(Point P, double val);

double point_dot(Point P1, Point P2);

#endif // POINT_H