# 2. Use CMake (with presets) to build and CTest to run tests

## Context

We need one description of the build that works on Linux, macOS and Windows, and a standard way to
run the tests.

Alternatives considered: hand-written Makefiles (Unix only), Meson, Bazel, IDE-specific project
files (Visual Studio, Xcode).

Our reason: CMake is common in C++ and cross-platform.

## Decision

We describe the build with CMake (≥ 3.25) in `CMakeLists.txt`, and the configurations
(`unix-debug`, `unix-release`, `windows`) in `CMakePresets.json`. Tests are registered with and run
by CTest, which ships with CMake.

## Status

Proposed

## Consequences

- One build description generates Makefiles, Ninja or Visual Studio projects.
- Most C++ libraries and IDEs understand CMake, so adding dependencies is easier.
- CMake is another language to learn, and its syntax is verbose and easy to get wrong.
- CTest does not compile: the project must be built before running `ctest`.
