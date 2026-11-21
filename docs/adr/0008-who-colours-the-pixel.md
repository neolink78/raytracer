# 8. A `trace` function decides the colour of a pixel

## Context

To make an image, every pixel needs a colour: send a ray, find what it hits, and choose the
object's colour or the background. The domain model left open who makes that choice:

- **The camera:** it sends the rays, but it does not know what is in the scene.
- **A sphere (or any shape):** it knows whether a ray hits it, but the background colour is not its
  business, and with several shapes none of them knows which hit is the nearest.
- **The image:** it holds the colours, but computing them would mix storage with rendering.
- **The main program:** the simplest place for a first spike, but `main` is not unit tested, so
  the decision would have no tests.

## Decision

A free function in `render/`, `trace`, takes a ray and what it can hit (one sphere at first, then
the scene) and returns a `Colour`: the colour of the nearest object hit, or the background colour
when nothing is hit.

The other classes keep one job each: the camera gives rays, shapes say whether and where a ray hits
them, the image stores colours. The code that loops over the pixels only writes `trace`'s result
into the image; it never chooses a colour itself.

## Status

Accepted

## Consequences

- The colour decision has its own unit tests (hit, miss, nearest of several objects), without a
  camera or an image.
- `main` only builds the objects and starts the rendering.
- `trace` will grow with the features (nearest hit, sky, then shading through a material); if it
  gets too big, moving it into a class will need a new ADR.
- A free function is not the usual object-oriented reflex; contributors must look in `render/` to
  find where colours are chosen.
