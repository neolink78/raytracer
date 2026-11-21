# Domain model

First model of the ray tracer, built from the client's explanation of ray tracing (milestone m1,
"Understanding the domain"). It shows the things of the domain and how they relate, not the code.

## How the renderer works

For each pixel of the image, the camera casts one ray from the eye through the pixel
(*backward tracing*). The first sphere the ray hits gives the pixel its colour; if the ray hits
nothing, the pixel takes the sky colour.

## Diagram

```mermaid
classDiagram
    class Vector {
        x
        y
        z
        add()
        subtract()
        scale()
        dot()
        length()
        normalised()
    }
    class Ray {
        origin
        direction
    }
    class Sphere {
        centre
        radius
        colour
    }
    class Camera {
        eye
    }
    class Image {
        width
        height
    }
    class Colour {
        r
        g
        b
    }

    Camera "1" --> "*" Ray : sends
    Ray "*" --> "0..1" Sphere : hits
    Ray "*" --> "1" Image : passes through one pixel of
    Image "1" --> "*" Colour : holds one per pixel
    Sphere "1" --> "1" Colour : has
    Camera ..> Vector : uses
    Ray ..> Vector : uses
    Sphere ..> Vector : uses
```

Only `Vector` shows operations: the other boxes show what each thing knows. The colour of a pixel
is chosen by `trace` (a function, so not a box): the colour of the sphere the ray hits, or the
background colour.

## The things

| Thing  | Knows                               | Can be asked                                   |
|--------|-------------------------------------|------------------------------------------------|
| Vector | x, y, z                             | add, subtract, scale, dot, length, normalised  |
| Ray    | an origin, a direction              | the point at distance t: P(t) = O + t·D, t ≥ 0 |
| Sphere | a centre, a radius, a colour        | does this ray hit me, and at which t?          |
| Camera | the eye position                    | the ray through a given pixel: D = pixel − eye |
| Image  | a width, a height, a colour per pixel | the colour of a pixel; set it                 |
| Colour | r, g, b between 0 and 1             | its r, g, b                                    |

## Decisions

The model left three questions open. Each one is recorded in an ADR:

| Question                                    | Decision                                  | ADR |
|---------------------------------------------|-------------------------------------------|-----|
| Is a colour a vector?                       | No: `Colour` is its own class             | [0006](../adr/0006-colour-is-not-a-vector.md) |
| Are points and directions the same class?   | Yes: both are `Vector`                    | [0007](../adr/0007-points-and-directions-are-vectors.md) |
| Who decides the colour of a pixel?          | A `trace` function, not the camera, shape or image | [0008](../adr/0008-who-colours-the-pixel.md) |
