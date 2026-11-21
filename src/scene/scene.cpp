#include "scene/scene.h"

#include <utility>

Scene::Scene(const Vector& toLight) : _toLight(toLight.normalised()) {}

Vector Scene::toLight() const { return _toLight; }

void Scene::add(std::unique_ptr<Shape> shape) { _shapes.push_back(std::move(shape)); }

std::optional<Hit> Scene::nearestHit(const Ray& ray) const {
    std::optional<Hit> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        std::optional<Hit> hit = shape->hit(ray);
        if (hit && (!nearest || hit->t < nearest->t)) {
            nearest = hit;
        }
    }
    return nearest;
}
