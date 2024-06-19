# Example Project

The goal of this project was to demonstrate several features of C in practice.

The `sample` folder showcases a sample run I did with the code, the
plot of the resulting simulation, and the actual output of the simulation.

## Libraries

There are two libraries: planet_lib and point_lib.

- `point_lib` defines a `Point` struct that is a member of a 2d vector space $\langle V, +, .\rangle$
  with corresponding operations

- `planet_lib` defines a `Planet` struct that carries additional information of mass, position,
  velocity, and whether or not the planet is allowed to move.
  - The position and velocity are stored as `Point` objects.
    This means that `planet_lib` has a dependency on `point_lib`.
    You can see how this is handled in `core/CmakeLists.txt`
  - `planet_lib` showcases many more features of C than `point_lib`

For both, I would recommend looking at the header file in their `inc`
folder before moving on to their source file in their `src` folder.

The header file can be thought of as a summary of all the info you need
to understand the source file and an overview of what it will contain.

I would recommend looking at the files for `point_lib` first and
`planet_lib` second as the former is a lot simpler than the latter.

Here is what the tree of this directory looks like:

## Tree

```plaintext
C:.
│   .gitignore
│   CMakeLists.txt
│   parse_simulation.py
│   README.md
│
├───core
│   │   CMakeLists.txt
│   │
│   ├───planet
│   │   ├───inc
│   │   │       planet.h
│   │   │
│   │   └───src
│   │           planet.c
│   │
│   └───point
│       ├───inc
│       │       point.h
│       │
│       └───src
│               point.c
│
├───sample
│       graph.png
│       README.md
│       simulation.txt
│
└───src
        main.c
```

## Note On Optimization

The code here is not optimized and there are several areas where it could be improved. Even so, it's good enough considering it can still compute thousands of loops per second.

For some examples:

- It doesn't take advantage of the fact that the force of gravity
  created by Planet A on Planet B is the negative of the force of gravity created by
  Planet B on Planet A.

- It also doesn't make use of vectorized or SIMD operations.
- It also traverses the planet array twice per loop. This introduces a slight overhead
that could be optimized.
