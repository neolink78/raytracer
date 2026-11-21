#include <catch2/catch_test_macros.hpp>

#include "render/trace.h"
#include "test_helpers.h"

static const Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
static const Material red(Colour(1, 0, 0));

TEST_CASE("trace gives the full colour where the sphere faces the sun") {
    Sphere sphere(Vector(0, 0, 9), 5, red);

    requireColoursEqual(trace(ray, sphere, Vector(0, 0, -1)), Colour(1, 0, 0));
}

TEST_CASE("trace darkens the colour when the sun comes from the side") {
    Sphere sphere(Vector(0, 0, 9), 5, red);

    requireColoursEqual(trace(ray, sphere, Vector(0.6, 0, -0.8)), Colour(0.8, 0, 0));
}

TEST_CASE("trace darkens the colour where the surface is tilted") {
    Sphere sphere(Vector(3, 0, 9), 5, red);

    requireColoursEqual(trace(ray, sphere, Vector(0, 0, -1)), Colour(0.8, 0, 0));
}

TEST_CASE("trace gives black when the ray misses the sphere") {
    Sphere sphere(Vector(6, 0, 9), 5, red);

    requireColoursEqual(trace(ray, sphere, Vector(0, 0, -1)), Colour(0, 0, 0));
}
