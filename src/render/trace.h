#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"

Colour trace(const Ray& ray, const Sphere& sphere, const Vector& toLight);
