#ifndef PLANET_H
#define PLANET_H

#include <stdio.h>
#include "point.h"

// Gravitational constant in N*m^2/kg^2
#define BIG_G 6.6743e-11 

typedef enum {
    PLANET_FIXED = 0,
    PLANET_MOVING = 1,
} planet_moving_t;

typedef struct Planet {
    double mass;      // kilograms
    Point position;   // meters
    Point velocity;   // meters per second
    planet_moving_t moving;
} Planet;

// Function prototypes
Planet planet_new(double mass, double x, double y, double Vx, double Vy);

Point planet_acceleration(Planet planet, Planet* p_arr, size_t num_p);

void planet_recalculate(Planet* planet, Point Accel, double DelT);

void planet_write_data(FILE* fptr, Planet* planet_arr, size_t num_planets);

void planet_write_stepsize(FILE* fptr, double stepsize);

void planet_write_motion_data(FILE* fptr, Planet* planet_arr, size_t num_planets, unsigned long timestep);

#endif // PLANET_H