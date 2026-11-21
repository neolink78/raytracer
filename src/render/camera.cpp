#include "render/camera.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth) {}

Ray Camera::rayThroughCentre() const { return Ray(_eye, _screenCentre - _eye); }
