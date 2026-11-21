#include <catch2/catch_test_macros.hpp>

#include "geometry/sphere.h"
#include "test_helpers.h"

static const Material red(Colour(1, 0, 0));

TEST_CASE("a ray through the centre of a sphere hits it") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, red);

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("a ray off the centre but inside the radius hits the sphere") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, red);

    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("a ray outside the radius misses the sphere") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, red);

    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("a sphere gives back its colour") {
    Sphere sphere(Vector(0, 0, 9), 5, Material(Colour(1, 0.5, 0)));

    requireColoursEqual(sphere.colour(), Colour(1, 0.5, 0));
}

TEST_CASE("a sphere behind the eye is not hit") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, red);

    REQUIRE_FALSE(sphere.isHitBy(ray));
}
