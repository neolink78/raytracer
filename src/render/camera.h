#pragma once

#include "geometry/ray.h"
#include "image/image.h"
#include "math/vector.h"
#include "scene/scene.h"

class Camera {
  public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    Ray rayThroughPixel(int column, int row, int width, int height) const;
    Image render(const Scene& scene, int width, int height) const;

  private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;
};
