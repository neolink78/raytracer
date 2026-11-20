# raytracer

A ray tracer written in C++20 — HETIC student project.

- Discovery report: [docs/discovery/discovery-report.md](docs/discovery/discovery-report.md)
- Architecture decisions: [docs/adr/](docs/adr/)
- How to contribute: [CONTRIBUTING.md](CONTRIBUTING.md)
- Code of conduct: [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)
- Licence: [Apache-2.0](LICENSE)

## Getting started (dev container, recommended)

The dev container gives everyone the same Linux, compiler (GCC/Clang), CMake and debugger,
whatever their OS.

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/) (or Docker Engine on Linux) and start it.
2. Open the project in an editor that supports dev containers:
   - **VS Code** with the *Dev Containers* extension: run *Dev Containers: Reopen in Container*.
   - **Zed**: accept the prompt, or run `projects: open dev container`.
3. Run every command below in the editor terminal, inside the container.

> **Windows:** clone the repository inside WSL, otherwise Git may convert line endings and break the `Makefile`.

## Build, run, test

| Command      | What it does                             |
|--------------|------------------------------------------|
| `make build` | configure and compile (`build/unix-debug`) |
| `make run`   | build, then run the program              |
| `make test`  | build, then run the tests                |
| `make clean` | delete the build folder                  |

`make run` prints `Hello, World!` and `make test` ends with `100% tests passed`.
Use `make PRESET=unix-release run` for an optimised build.

The same thing with CMake directly:

```sh
cmake --preset unix-debug          # configure
cmake --build --preset unix-debug  # compile
./build/unix-debug/raytracer       # run
ctest --preset unix-debug          # test (CTest does not compile: build first)
```

### Windows without the container

Requires Visual Studio 2022 (C++ workload), CMake ≥ 3.25 and Git.

```powershell
cmake --workflow --preset windows-debug          # configure, build, test
cmake --build --preset windows-debug-run         # run
cmake --build --preset windows-debug-clean       # clean
```

## Tests and TDD

Tests use [Catch2 v3](https://github.com/catchorg/Catch2), downloaded automatically on the first
configure (internet needed once), and are run by CTest.

- Production code goes in `src/` and is compiled into the `raytracer_core` library.
- Tests go in `tests/test_*.cpp` and link against `raytracer_core`.

TDD loop:

1. **Red** — write a failing test in `tests/`:
   ```cpp
   #include <catch2/catch_test_macros.hpp>
   #include "greeting.h"

   TEST_CASE("greeting uses the given name") {
       REQUIRE(greeting("Ray") == "Hello, Ray!");
   }
   ```
   A new test file must be added to `add_executable(raytracer_tests ...)` in `tests/CMakeLists.txt`.
2. Run `make test` and watch it fail.
3. **Green** — write the minimum code in `src/` to make it pass (new `.cpp` files go in
   `add_library(raytracer_core ...)` in `CMakeLists.txt`).
4. **Refactor** — clean up, `make test` stays green.

Run a single test: `./build/unix-debug/tests/raytracer_tests "greeting uses the given name"`.

## Project layout

```
.devcontainer/   dev container (Dockerfile + config)
src/             program code (raytracer_core library + main.cpp)
tests/           Catch2 tests
docs/adr/        architecture decision records
docs/discovery/  discovery report (milestone m0)
.github/         CI workflow, pull request and issue templates
```

## Contributing

Read [CONTRIBUTING.md](CONTRIBUTING.md) before opening a pull request. Every pull request is built
and tested by the CI ([.github/workflows/ci.yml](.github/workflows/ci.yml)) inside the same dev
container. Participation is covered by our [Code of Conduct](CODE_OF_CONDUCT.md).

## Licence

Licensed under the [Apache License 2.0](LICENSE).
