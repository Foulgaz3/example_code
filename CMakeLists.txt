cmake_minimum_required(VERSION 3.10)

project(PlanetOrbitSimulation)

add_subdirectory(core)

add_executable(PlanetOrbit src/main.c)

target_link_libraries(PlanetOrbit
    planet_lib
    point_lib
)
