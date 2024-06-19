# point lib
add_library(point_lib STATIC
    point/src/point.c  # Path to the source file
)

target_include_directories(point_lib PUBLIC
    point/inc  # Path to the include directory
)

# planet lib
add_library(planet_lib STATIC
    planet/src/planet.c  # Path to the source file
)

target_include_directories(planet_lib PUBLIC
    planet/inc  # Path to the include directory
)

# Link point_lib to planet_lib
target_link_libraries(planet_lib PUBLIC point_lib)