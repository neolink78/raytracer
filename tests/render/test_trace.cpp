#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "geometry/sphere.h"
#include "render/trace.h"
#include "test_helpers.h"

static const Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
static const Material red(Colour(1, 0, 0));

TEST_CASE("trace gives the full colour where the sphere faces the sun") {
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(1, 0, 0));
}

TEST_CASE("trace darkens the colour when the sun comes from the side") {
    Scene scene(Vector(0.6, 0, -0.8));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(0.8, 0, 0));
}

TEST_CASE("trace darkens the colour where the surface is tilted") {
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(3, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(0.8, 0, 0));
}

TEST_CASE("trace gives black when the ray misses every shape") {
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, red));

    requireColoursEqual(trace(ray, scene), Colour(0, 0, 0));
}
