#pragma once

#include "colour/colour.h"
#include "geometry/ray.h"
#include "scene/scene.h"

Colour trace(const Ray& ray, const Scene& scene);
