# 10. Left-handed coordinates: x right, y up, z away from the eye

## Context

Every position in the scene (the eye, the screen, the spheres) is three numbers, so we must agree
on what each axis means. Without a written convention, one person puts a sphere at z = 9 and
another at z = −9, and the picture comes out empty, upside down or mirrored. It will matter even
more when pixel columns and rows become x and y on the screen.

Alternatives considered:

- **Right-handed, the camera looking towards −z** (x right, y up, z towards the viewer): the usual
  convention in OpenGL and in *Ray Tracing in One Weekend*. But every object in front of the camera
  then has a negative z, which is easy to get wrong in tests and examples.
- **z up** (as in Blender and many CAD tools): natural for floors and terrain, but it does not match
  the course material or the screen, where y is up.

## Decision

We use a left-handed coordinate system:

- **x** points to the right,
- **y** points up,
- **z** points forward, away from the eye, into the scene.

The eye is in front of the screen on the z axis (for example at (0, 0, −1) with the screen centre at
(0, 0, 0)), so objects in front of the camera have a larger z than the screen.

## Status

Accepted

## Consequences

- Objects in front of the camera have positive z, which keeps test values and examples simple.
- Code and examples from right-handed sources (OpenGL, *Ray Tracing in One Weekend*) must flip the
  sign of z before they are reused here.
- Assets exported from right-handed or z-up tools (Maya is y-up right-handed, Blender z-up) will
  need a conversion when the studio imports its scenes.
- Pixel rows grow downwards in an image file while y grows upwards: the camera must flip y when it
  turns a row into a position.
