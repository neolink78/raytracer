# 7. Points and directions share the Vector class

## Context

A ray has an origin (a point: *where*) and a direction (*which way*). A sphere has a centre and a
camera has an eye, both points. Points and directions are both three numbers, and the arithmetic
we need is the same: P(t) = O + t·D, D = pixel − eye, and the sphere intersection uses O − C.

Some operations only make sense for one of them: adding two points means nothing, and
normalising a point means nothing. Separate classes would let the compiler reject them.

Alternatives considered:

- **Separate `Point` and `Direction` classes:** safer (`point + point` does not compile), but every
  formula needs the right conversions (`point − point → direction`, `point + direction → point`),
  which doubles the classes and tests for a team new to C++ and slows the first milestone down.
- **One `Vector` class plus type aliases (`using Point = Vector`):** more readable names, but the
  compiler still sees one type, so it gives no extra safety and may suggest it does.

## Decision

Points and directions are both `Vector` (`x`, `y`, `z` as `double`, immutable). Their role is
given by the variable name: `origin`, `centre`, `eye` for points; `direction`, `normal` for
directions.

## Status

Accepted

## Consequences

- One class to write and test; the formulas from the course translate directly into code.
- The compiler accepts meaningless operations such as `point + point`; only names, reviews and
  tests catch them.
- Functions that need a unit direction must say so (in the name or a comment) and normalise it.
- If these mistakes become frequent, splitting into `Point` and `Direction` stays possible in a
  new ADR, but it would touch every class that uses `Vector`.
