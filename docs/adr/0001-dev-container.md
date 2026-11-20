# 1. Use a dev container for the development environment

## Context

The project must compile and run the same way for every contributor, on macOS, Windows and Linux,
including partner studios with machines we do not control. Installing a C++ toolchain by hand gives
each person a different compiler and version ("works on my machine").

Alternatives considered, and why they fit worse:

- **Each contributor installs the tools natively:** everyone ends up with a different compiler
  and version (GCC, Clang, MSVC), so code that builds on one machine can fail on another. Beginners
  also lose time installing and configuring a toolchain instead of writing code.
- **A setup script per OS:** three scripts (Linux, macOS, Windows) to write and keep in sync, which
  nobody can test on every OS; versions still drift with each system's package manager.
- **A virtual machine (e.g. Vagrant):** gives the same environment, but is heavy (a full OS, several
  GB, slow to start) and poorly integrated with our editors.

Our reason: the environment is described once, in the repository, and VS Code and Zed open it
directly. Every contributor gets the same compiler and tools in one step, and the CI can reuse the
same image, so "it passes on my machine" means "it passes in CI".

## Decision

We develop inside a dev container defined in `.devcontainer/` (Ubuntu 24.04 with CMake, GCC/Clang,
clangd, clang-format and gdb), opened with VS Code or Zed.

## Status

Accepted

## Consequences

- Everyone builds and tests with the same Linux toolchain; onboarding is "open in container".
- Docker is required, and the first start downloads and builds an image (several minutes).
- It standardises the tools, not the CPU: ARM Macs and x86-64 PCs can still differ in timing and
  floating-point output.
- Native macOS and Windows builds are not tested by the container.
