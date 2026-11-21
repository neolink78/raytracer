# Contributing

Thank you for your interest in the ray tracer. This guide explains how to set up the project,
make a change and submit it.

By taking part, you agree to follow our [Code of Conduct](CODE_OF_CONDUCT.md).

## Set up the dev container

All work happens inside the dev container, so everyone uses the same compiler and tools
(see [ADR 0001](docs/adr/0001-dev-container.md)).

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/) (or Docker Engine on
   Linux) and start it.
2. Open the project in VS Code (*Dev Containers* extension: *Reopen in Container*) or Zed
   (`projects: open dev container`).
3. Run every command in the editor terminal, inside the container.

On Windows, clone the repository inside WSL, otherwise line endings may break the `Makefile`.

## Commands

| Command      | What it does                  |
|--------------|-------------------------------|
| `make build` | configure and compile         |
| `make run`   | build, then run the program   |
| `make test`  | build, then run the tests     |
| `make clean` | delete the build folder       |

Run `make test` before opening a pull request: the CI runs the same command in the same
container and must pass.

## Work with TDD

We write the test first ([ADR 0003](docs/adr/0003-catch2.md): Catch2).

1. **Red:** write a failing test in the folder matching the code (`tests/math/test_vector.cpp` for
   `src/math/vector.cpp`) and add new test files to `tests/CMakeLists.txt`.
2. Run `make test` and check that it fails for the expected reason.
3. **Green:** write the minimum code in `src/` to make it pass (new `.cpp` files go in
   `add_library(raytracer_core ...)` in `CMakeLists.txt`).
4. **Refactor:** clean up while `make test` stays green.

The [README](README.md#tests-and-tdd) has an example.

## Architecture decisions (ADRs)

Our decisions about tools, build and tests are recorded in [`docs/adr/`](docs/adr/).

- Read them before changing the build, the tools or the test setup.
- Do not go against an accepted ADR. To change a decision, or to add a new tool or service, add a
  new ADR (next number, format: Title, Context, Decision, Status, Consequences) with status
  `Proposed`, and explain it in your pull request.
- Only the maintainers set an ADR to `Accepted`.

## Submit a change

1. Create a branch from `main`.
2. Make your change with its tests; keep `make test` green.
3. Open a pull request and fill in the template.
4. Wait for the CI to pass.

To report a bug or suggest a feature, open an issue and pick the matching template.
