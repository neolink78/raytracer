#pragma once

#include "math/vector.h"

class Ray {
  public:
    Ray(const Vector& origin, const Vector& direction);

    Vector origin() const;
    Vector direction() const;
    Vector at(double t) const;

  private:
    Vector _origin;
    Vector _direction;
};
