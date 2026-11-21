#include <catch2/catch_test_macros.hpp>

#include "render/trace.h"
#include "test_helpers.h"

TEST_CASE("trace gives the sphere's colour when the ray hits it") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Material(Colour(1, 0, 0)));

    requireColoursEqual(trace(ray, sphere), Colour(1, 0, 0));
}

TEST_CASE("trace gives black when the ray misses the sphere") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Material(Colour(1, 0, 0)));

    requireColoursEqual(trace(ray, sphere), Colour(0, 0, 0));
}
