# 6. A colour is its own class, not a Vector

## Context

A colour is three numbers (r, g, b), like a vector is three numbers (x, y, z). Reusing `Vector`
for colours would save a class. But they are different knowledge:

- Colours get mixed, are kept between 0 and 1, and are turned into 0–255 for an image file.
- A colour has no use for `dot`, `length` or `normalised`, and a direction has no use for 0–255.
- Adding a colour to a position means nothing, but with one class the compiler would accept it.

Two classes with similar lines are not a DRY violation: DRY is about knowledge, not similar code.

Alternatives considered:

- **Use `Vector` for colours:** one class less, but code would read `colour.x()` for red, the
  compiler would accept a direction where a colour is expected, and `Vector` would grow
  colour-only methods.
- **A common base class or template for "three numbers":** removes the similar lines, but adds an
  abstraction we do not need and makes compiler errors harder to read for a team new to C++.

## Decision

`Colour` is a class of its own, with three `double`s read through `r()`, `g()` and `b()`, in its
own `colour/` folder (both `geometry/` and `render/` use it). Like `Vector`, it is immutable.

It starts with no arithmetic. Operations (for example scaling by a brightness) are added only when
a test needs them. What happens to values outside 0–1 (clamp them, or refuse them) is not decided
yet: it will be decided, and recorded, when an image file needs 0–255 values.

## Status

Accepted

## Consequences

- Code reads in the domain's words (`colour.r()`), and the compiler rejects a colour where a
  position is expected, and the reverse.
- Arithmetic that both classes need (such as scaling) is written and tested twice.
- Out-of-range values are not checked yet: a bug producing r = 1.7 would go unnoticed until the
  clamp-or-refuse decision is made.
- If colours later need more channels (alpha, spectral rendering), only `Colour` changes.
