#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <optional>

#include "geometry/sphere.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

static const Material red(Colour(1, 0, 0));

TEST_CASE("hit gives the nearest point in front of the ray, its normal and the material") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
    requireColoursEqual(hit->material.colour(), Colour(1, 0, 0));
}

TEST_CASE("hit off the centre gives a tilted normal") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(6, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 5));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0, -0.8));
}

TEST_CASE("hit gives nothing when the ray misses the sphere") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, red);

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("hit gives nothing for a sphere behind the eye") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, red);

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("a ray starting inside the sphere hits it on the way out") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 1), 5, red);

    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(7, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 6));
    requireVectorsEqual(hit->normal, Vector(0, 0, 1));
}
