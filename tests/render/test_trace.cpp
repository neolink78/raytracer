#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "render/trace.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("trace gives the sphere's colour when the ray hits it") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Colour colour = trace(ray, sphere);

    REQUIRE_THAT(colour.r(), WithinAbs(1, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0, tolerance));
}

TEST_CASE("trace gives black when the ray misses the sphere") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));

    Colour colour = trace(ray, sphere);

    REQUIRE_THAT(colour.r(), WithinAbs(0, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0, tolerance));
}
