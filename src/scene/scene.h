#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "math/vector.h"

class Scene {
  public:
    // toLight is the direction towards the sun; the scene keeps it as a unit vector.
    explicit Scene(const Vector& toLight);

    Vector toLight() const;
    void add(std::unique_ptr<Shape> shape);
    std::optional<Hit> nearestHit(const Ray& ray) const;

  private:
    Vector _toLight;
    std::vector<std::unique_ptr<Shape>> _shapes;
};
