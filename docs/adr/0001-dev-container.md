# 1. Use a dev container for the development environment

## Context

The project must compile and run the same way for every contributor, on macOS, Windows and Linux,
including partner studios with machines we do not control. Installing a C++ toolchain by hand gives
each person a different compiler and version ("works on my machine").

Alternatives considered: each contributor installs the tools natively; a package manager
script per OS; a virtual machine (e.g. Vagrant).

Our reason: the same tools for everyone.

## Decision

We develop inside a dev container defined in `.devcontainer/` (Ubuntu 24.04 with CMake, GCC/Clang,
clangd, clang-format and gdb), opened with VS Code or Zed.

## Status

Proposed

## Consequences

- Everyone builds and tests with the same Linux toolchain; onboarding is "open in container".
- Docker is required, and the first start downloads and builds an image (several minutes).
- It standardises the tools, not the CPU: ARM Macs and x86-64 PCs can still differ in timing and
  floating-point output.
- Native macOS and Windows builds are not tested by the container.
