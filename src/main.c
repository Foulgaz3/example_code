
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <point.h>
#include <planet.h>

int main() {

    unsigned long steps = 270;
    double step_size = 86400.; // sec // 86 400 seconds in a day 

    Planet Sun = planet_new(1.989e30, 0., 0., 0., 0.);
    Planet Earth = planet_new(5.972e24, 1.5e11, 0., 0., 2.985e4);

    Planet planets[] = {Sun, Earth};
    size_t num_planets = sizeof(planets) / sizeof(Planet);

    FILE *fptr;
    fptr = fopen("simulation.txt", "w");
    if (!fptr) {
        printf("ERROR OPENING FILE\n");
        return 1;
    }

    planet_write_data(fptr, planets, num_planets);
    
    planet_write_stepsize(fptr, step_size);

    fprintf(fptr, "MOTION\ntimestep, id, x, y, Vx, Vy\n");
    
    for (unsigned long t = 0; t < steps; t++) {
        for (size_t i = 0; i < num_planets; i++) {
            const Point accel = planet_acceleration(planets[i], planets, num_planets);
            planet_recalculate(&planets[i], accel, step_size);
        }
        planet_write_motion_data(fptr, planets, num_planets, t);
    }


    
free_resources:
    fclose(fptr);
    return 0;
}