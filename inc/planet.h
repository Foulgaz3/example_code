#ifndef PLANET_H
#define PLANET_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "point.h"

// N*m2/kg2
#define BIG_G 6.6743e-11 

typedef enum {
    PLANET_FIXED = false,
    PLANET_MOVING = true,
} planet_moving_t;

typedef struct Planet {
    double mass; // kilograms
    Point position; // meters
    Point velocity;
    planet_moving_t moving;
} Planet;

Planet planet_new(double mass, double x, double y, double Vx, double Vy) {
    Planet new_planet;
    new_planet.mass = mass;
    new_planet.position = (Point) {x, y};
    new_planet.velocity = (Point) {Vx, Vy};
    new_planet.moving = PLANET_MOVING; // default to moving
    return new_planet;
}

Point planet_acceleration(Planet planet, Planet* p_arr, size_t num_p) {
    Point Accel = {0., 0.}; // (m/s^2)
    if (planet.moving) {
        for (size_t i = 0; i < num_p; i++) {
            Planet other_planet = p_arr[i];

            if (&planet != &other_planet) {
                // Delta position (m)
                const Point DelP = point_sub(other_planet.position, planet.position); 
                // Distance squared (m^2)
                const double r2 = point_dot(DelP, DelP);

                if (r2 != 0.0) {
                    const double scale = other_planet.mass / (r2 * sqrt(r2));

                    const Point vector_accel = point_scale(DelP, scale);

                    Accel = point_add(Accel, vector_accel);
                }
            }
        }
        Accel = point_scale(Accel, BIG_G);
    }
    return Accel;
}

void planet_recalculate(Planet* planet, Point Accel, double DelT) {
    double DelT_acc = DelT * DelT * 0.5;
    // updating planet position
    planet->position.X = planet->position.X + DelT*planet->velocity.X + DelT_acc*Accel.X;
    planet->position.Y = planet->position.Y + DelT*planet->velocity.Y + DelT_acc*Accel.Y;
    // updating planet velocity
    planet->velocity.X = planet->velocity.X + DelT*Accel.X;
    planet->velocity.Y = planet->velocity.Y + DelT*Accel.Y;
}

void planet_write_data(FILE* fptr, Planet* planet_arr, size_t num_planets) {
    fprintf(fptr, "BODIES\nid, mass, x, y, Vx, Vy, moves\n");

    for (size_t i = 0; i < num_planets; i++) {
        Planet p = planet_arr[i];

        // Estimate the length of the string
        size_t string_length = snprintf(NULL, 0, 
                                        "%llu, %e, %e, %e, %e, %e, %i\n", 
                                        i, 
                                        p.mass, 
                                        p.position.X, 
                                        p.position.Y,
                                        p.velocity.X,
                                        p.velocity.Y,
                                        p.moving);
        
        // Allocate memory for the string
        char* string = (char*)malloc(string_length + 1);  // +1 for the null terminator
        if (!string) {
            printf("ERROR ALLOCATING MEMORY\n");
            return;  // Exit function on error
        }

        // Format the string
        snprintf(string, string_length + 1, 
                 "%llu, %e, %e, %e, %e, %e, %i\n", 
                 i, 
                 p.mass, 
                 p.position.X, 
                 p.position.Y,
                 p.velocity.X,
                 p.velocity.Y,
                 p.moving);

        // Write to file
        fprintf(fptr, "%s", string);

        // Free the allocated memory
        free(string);
    }
}

// Function to write stepsize to file
void write_stepsize(FILE* fptr, double stepsize) {
    // Estimate the length of the string
    size_t string_length = snprintf(NULL, 0, "STEPSIZE: %e sec\n", stepsize);

    // Allocate memory for the string
    char* string = (char*)malloc(string_length + 1);  // +1 for the null terminator
    if (!string) {
        printf("ERROR ALLOCATING MEMORY\n");
        return;  // Exit function on error
    }

    // Format the string
    snprintf(string, string_length + 1, "STEPSIZE: %e sec\n", stepsize);

    // Write to file
    fprintf(fptr, "%s", string);

    // Free the allocated memory
    free(string);
}

void planet_write_motion_data(FILE* fptr, Planet* planet_arr, size_t num_planets, unsigned long timestep) {
    for (size_t i = 0; i < num_planets; i++) {
        Planet p = planet_arr[i];
        if (p.moving) {
            // format is : "timestep, id, x, y, Vx, Vy"
            // Estimate the length of the string
            size_t string_length = snprintf(NULL, 0, 
                                            "%lu, %zu, %e, %e, %e, %e\n", 
                                            timestep, 
                                            i, 
                                            p.position.X, 
                                            p.position.Y,
                                            p.velocity.X,
                                            p.velocity.Y);
            
            // Allocate memory for the string
            char* string = (char*)malloc(string_length + 1);  // +1 for the null terminator
            if (!string) {
                printf("ERROR ALLOCATING MEMORY\n");
                return;  // Exit function on error
            }

            // Format the string
            snprintf(string, string_length + 1, 
                    "%lu, %zu, %e, %e, %e, %e\n", 
                    timestep, 
                    i, 
                    p.position.X, 
                    p.position.Y,
                    p.velocity.X,
                    p.velocity.Y);

            // Write to file
            fprintf(fptr, "%s", string);

            // Free the allocated memory
            free(string);
        }
    }
}

#endif // PLANET_H