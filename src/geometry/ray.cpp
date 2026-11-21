#include "geometry/ray.h"

Ray::Ray(const Vector& origin, const Vector& direction) : _origin(origin), _direction(direction) {}

Vector Ray::origin() const { return _origin; }

Vector Ray::direction() const { return _direction; }

Vector Ray::at(double t) const { return _origin + t * _direction; }
