# 11. Save images as PNG with LodePNG

## Context

The renderer now fills an `Image` in memory. The client must open our pictures in the image
viewers it already uses, so we must write a standard file format. PNG is lossless, compressed and
opened everywhere: the 400×300 test picture is about 735 bytes as PNG, against 360 KB as binary
PPM and 804 KB as text PPM.

Writing PNG by hand means implementing zlib compression and CRC checksums, so we use a library.
Our criteria: a licence compatible with our Apache-2.0 open-source licence, nothing to
install in the dev container, fetchable by CMake like Catch2 (ADR 0003), a C++ API that the team
can read, and active maintenance. Speed matters less for now.

Options considered:

- **libpng:** the reference implementation, but a C API that needs many calls and manual error
  handling, and it depends on zlib: both must be installed in the Dockerfile.
- **stb_image_write:** a single header, public domain or MIT, but a C API with `void*` buffers, and
  it writes larger PNG files.
- **LodePNG:** one `.cpp` and one `.h`, zlib licence, no dependency, a C++ API with
  `std::vector<unsigned char>`. It is the slowest of the three to save.
- **PPM written by hand:** no library at all, but huge files that most viewers cannot open.

Not chosen for now: OpenCV and ImageMagick (far too large for writing one format), fpng and libspng
(faster, but less simple to integrate). OpenEXR is the format film studios use for high dynamic
range; it is a likely future need.

## Decision

We save PNG files with LodePNG (https://github.com/lvandeve/lodepng), fetched by CMake
`FetchContent` and pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409` (the project
publishes no releases). It is compiled as a static library, without our warning flags.

Only `src/output/` uses LodePNG, behind our own `ImageSaver` interface: a `PngSaver` class adapts
LodePNG to our `Image`. The rest of the code only knows "an image saver". The only other place that
includes LodePNG is the test of `PngSaver`, which reads the saved file back to check its bytes.

## Status

Accepted

## Consequences

- Our pictures open in any viewer, and the files are small.
- Nothing to install: the first configure downloads LodePNG, so it needs internet access, like
  Catch2.
- The pin is a commit hash, not a version: upgrades are manual, and we must check the project's
  history ourselves.
- LodePNG is slower than libpng or fpng; for film-size renders, saving may become a bottleneck.
- The zlib licence requires keeping LodePNG's licence notice in its source files, and marking any
  file we alter; an acknowledgement in our documentation is optional.
- The `ImageSaver` interface is one more layer to read and maintain while it has a single
  implementation. It pays off when a second format (such as EXR) arrives: one new class, and
  nothing else changes.
