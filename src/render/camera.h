#pragma once

#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "math/vector.h"

class Camera {
  public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    Ray rayThroughCentre() const;
    Ray rayThroughPixel(int column, int row, int width, int height) const;
    Image render(const Sphere& sphere, int width, int height) const;

  private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;
};
