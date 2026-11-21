#pragma once

#include <optional>

#include "geometry/hit.h"
#include "geometry/ray.h"
#include "material/material.h"
#include "math/vector.h"

class Sphere {
  public:
    Sphere(const Vector& centre, double radius, const Material& material);

    std::optional<Hit> hit(const Ray& ray) const;

  private:
    Vector _centre;
    double _radius;
    Material _material;
};
