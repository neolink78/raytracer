#pragma once

#include "material/material.h"
#include "math/vector.h"

// Where a ray meets a shape: how far along the ray (t), the point, the unit normal there, and the
// material of the shape.
struct Hit {
    double t;
    Vector point;
    Vector normal;
    Material material;
};
