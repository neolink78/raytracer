# 9. One folder per concept in `src/`, mirrored in `tests/`

## Context

All the code is in one flat `src/` folder, and all the tests in one flat `tests/` folder. With
`Vector` it is still fine, but the domain model already has Ray, Sphere, Camera, Image and Colour,
and the shading brings materials, shapes and a scene. A flat folder will not scale: a class and its
tests should be easy to find by the concept they belong to.

## Decision

- Each domain concept gets its own folder under `src/`: `src/math/` (Vector) first; then, as their
  first class arrives, folders such as `src/geometry/`, `src/colour/` and `src/render/`.
- A folder is created with its first class, not before.
- `tests/` mirrors `src/`: the tests of `src/math/vector.cpp` are in `tests/math/test_vector.cpp`.
- Includes are written from `src/`: `#include "math/vector.h"`, never `"../math/vector.h"`.
- `main.cpp` stays at the root of `src/`.

Options deliberately left out for now, and when each would become worth it:

- **Namespaces:** when two names clash, or when partner studios embed our code in theirs.
- **One library per folder:** when we want CMake to enforce the dependencies between folders (for
  example, `math/` must not depend on `render/`), or when build times grow.
- **A separate `include/` folder for public headers:** when the renderer is shipped as a library.

## Status

Accepted

## Consequences

- A class and its tests are found by concept, in matching paths.
- An include says where the header lives (`"math/vector.h"`), so two headers with the same name in
  different folders do not clash.
- Every new `.cpp` must still be added by hand to `CMakeLists.txt` or `tests/CMakeLists.txt`.
- Nothing stops a folder from including any other: a dependency loop (for example
  `geometry/` → `render/` → `geometry/`) is only caught by review, until we split into libraries.
- Choosing a folder name is a design decision: a wrong concept means moving files later.
