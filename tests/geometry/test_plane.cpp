#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <optional>

#include "geometry/plane.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

static const Material green(Colour(0, 1, 0));
static const Plane floorPlane(Vector(0, 0, 0), Vector(0, 1, 0), green);

TEST_CASE("a ray going down hits the floor") {
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    std::optional<Hit> hit = floorPlane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(6, 0, 0));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
    requireColoursEqual(hit->material.colour(), Colour(0, 1, 0));
}

TEST_CASE("a tilted plane gives its normal as a unit vector") {
    Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), green);
    Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));

    std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 6, 0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0));
}

TEST_CASE("a ray parallel to the floor never hits it") {
    Ray ray(Vector(0, 8, 0), Vector(5, 0, 0));

    REQUIRE_FALSE(floorPlane.hit(ray).has_value());
}

TEST_CASE("a ray going away from the floor does not hit it") {
    Ray ray(Vector(0, 8, 0), Vector(3, 4, 0));

    REQUIRE_FALSE(floorPlane.hit(ray).has_value());
}
