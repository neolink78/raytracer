#pragma once

#include "colour/colour.h"
#include "math/vector.h"

class Material {
  public:
    explicit Material(const Colour& colour);

    Colour colour() const;
    Colour shade(const Vector& normal, const Vector& toLight) const;

  private:
    Colour _colour;
};
