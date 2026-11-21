# 12. A shape has a material (composition, not inheritance)

## Context

With Lambert's law, the colour of a point depends on how the surface reacts to light, not only on
its colour. That reaction belongs to a *material*. We now have two shapes (sphere and plane), and
more of both will come: shapes such as triangles or boxes, and materials such as mirrors, glass or
shiny paint.

We must decide how a shape and a material relate.

Alternatives considered:

- **A shape *is a* material (inheritance):** for example `RedMatteSphere : Sphere` or
  `MirrorPlane : Plane`. Every new shape or material needs a class for each combination, so the
  number of classes is shapes × materials. The same shape could not change its material without
  changing its type, and the shading code would be copied into every subclass.
- **The renderer decides the colour, and shapes only hold a colour:** keeps shapes simple, but
  `trace` would then grow a branch for each kind of material, and adding one would change it.

## Decision

A shape *has a* material: `Sphere` and `Plane` each hold a `Material`, given to their constructor.
When a ray hits a shape, the `Hit` carries that material, and `trace` asks it for the colour:
`hit->material.shade(hit->normal, scene.toLight())`. The shape knows the geometry (where and
which way), the material knows the light (what colour).

## Status

Accepted

## Consequences

- Shapes and materials vary independently: the number of classes is shapes + materials, and any
  shape can use any material.
- A new shape (one class implementing `Shape`) changes no existing class; it only forwards its
  material into the `Hit`.
- `Material` is a concrete class today. A second kind of material (mirror, glass) will need an
  interface, like `Shape`, and a new ADR.
- Every shape must store a material and copy it into each `Hit`: some repetitive plumbing, and a
  copy of the material per hit.
