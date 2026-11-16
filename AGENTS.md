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

## Architecture decisions

- Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools
  or the test setup.
- Never go against an accepted ADR. To change a decision, write a new ADR with status
  `Proposed` and ask the maintainer.
- Never set an ADR to `Accepted`.
