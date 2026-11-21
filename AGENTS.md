# AGENTS.md

C++20 ray tracer. Work inside the dev container (`.devcontainer/`).

## Commands

```sh
make build   # configure + compile (CMake preset unix-debug)
make run     # build, then run ./build/unix-debug/raytracer
make test    # build, then run the Catch2 tests with CTest
make clean   # delete the build folder
```

Without make: `cmake --preset unix-debug`, `cmake --build --preset unix-debug`,
`ctest --preset unix-debug` (CTest does not compile: build first).
Windows without the container: `cmake --workflow --preset windows-debug`.

## Project structure

- One folder per concept under `src/` (`src/math/vector.h`, ...); a folder is created with its
  first class. `main.cpp` stays at the root of `src/`. See ADR 0009.
- Tests mirror `src/`: the tests of `src/math/vector.cpp` are in `tests/math/test_vector.cpp`.
- Includes start from `src/`: `#include "math/vector.h"`.
- New `.cpp` files must be added to `CMakeLists.txt` (code) or `tests/CMakeLists.txt` (tests).

## How we work

- TDD: write a failing test first, then the minimum code to pass it, then refactor.
- Expected values in tests come from the maths, not from the code's output. Never change an
  expected value without asking.
- Small steps: do only what is asked, nothing more.
- Simple C++: no templates, macros or clever tricks the team cannot explain.
- Never build or run anything on the host: the maintainer runs `make test` in the dev container.

## Architecture decisions

- Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools
  or the test setup.
- Never go against an accepted ADR. To change a decision, write a new ADR with status
  `Proposed` and ask the maintainer.
- Never set an ADR to `Accepted`.

## Contributing

- Contribution workflow (dev container, TDD, ADRs, pull requests): `CONTRIBUTING.md`.
- The CI (`.github/workflows/ci.yml`) runs `make test` in the dev container on every pull request:
  keep it green.
- Pull request and issue templates are in `.github/`. Code of conduct: `CODE_OF_CONDUCT.md`.
  Licence: Apache-2.0 (`LICENSE`).
