#include "geometry/plane.h"

Plane::Plane(const Vector& point, const Vector& normal, const Material& material)
    : _point(point), _normal(normal.normalised()), _material(material) {}

std::optional<Hit> Plane::hit(const Ray& ray) const {
    double nDotD = _normal.dot(ray.direction());
    if (nDotD == 0.0) {
        return std::nullopt;
    }
    double t = _normal.dot(_point - ray.origin()) / nDotD;
    if (t <= 0.0) {
        return std::nullopt;
    }
    return Hit{t, ray.at(t), _normal, _material};
}
