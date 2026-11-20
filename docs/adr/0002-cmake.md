# 2. Use CMake (with presets) to build and CTest to run tests

## Context

We need one description of the build that works on Linux, macOS and Windows (including native
Visual Studio), and a standard way to run the tests. The team is new to C++, so the tool must be
well documented and supported by our editors (VS Code, Zed).

Alternatives considered, and why they fit worse:

- **Hand-written Makefiles:** Unix only, so no native Windows build. Header dependencies and
  compiler flags must be tracked by hand, which is error-prone for beginners.
- **Meson:** cleaner syntax and a credible option, but fewer libraries, tutorials and IDE
  integrations support it; most C++ learning material assumes CMake.
- **Bazel:** designed for very large, multi-language codebases; its setup costs far more than it
  returns for one small program.
- **IDE project files (Visual Studio, Xcode):** each ties the build to one IDE on one OS, which
  defeats the shared dev container.

Our reason: CMake is the de facto standard for C++. It is cross-platform, understood by most
libraries and IDEs, and has the most learning material. Meson would also work, but is less common.

## Decision

We describe the build with CMake (≥ 3.25) in `CMakeLists.txt`, and the configurations
(`unix-debug`, `unix-release`, `windows`) in `CMakePresets.json`. Tests are registered with and run
by CTest, which ships with CMake. Running the test program directly would work too, but CTest gives
one standard command (`ctest --preset ...`) and editor test-panel integration at no extra cost.

## Status

Accepted

## Consequences

- One build description generates Makefiles, Ninja or Visual Studio projects.
- Most C++ libraries and IDEs understand CMake, so adding dependencies is easier.
- CMake is another language to learn, and its syntax is verbose and easy to get wrong.
- CTest does not compile: the project must be built before running `ctest`.
- This choice would be wrong if the project only targeted one platform and one IDE; that is not
  our case.
