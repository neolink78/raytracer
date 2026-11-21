#include "render/trace.h"

#include <optional>

Colour trace(const Ray& ray, const Sphere& sphere, const Vector& toLight) {
    std::optional<Hit> hit = sphere.hit(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material.shade(hit->normal, toLight);
}
