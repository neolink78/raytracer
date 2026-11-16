# 4. Use a Makefile for short commands

## Context

The CMake preset commands are long and hard to remember (`cmake --build --preset unix-debug`, …).
We want short commands like `npm run` scripts: build, run, test, clean.

Alternatives considered: shell scripts, `just`, CMake workflow presets only, VS Code tasks.

## Decision

A root `Makefile` wraps the CMake presets with `make build`, `make run`, `make test` and
`make clean`. The preset can be changed with `PRESET=...` (default `unix-debug`).

## Status

Proposed

## Consequences

- Short commands, documented in the README and `AGENTS.md`.
- `make` is already in the dev container; it is not available on Windows without the container,
  where the CMake presets are used directly.
- Makefile recipes need tabs and LF line endings (`.gitattributes` enforces LF).
- The Makefile only wraps CMake: build logic must stay in `CMakeLists.txt`.
