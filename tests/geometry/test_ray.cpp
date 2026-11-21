#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.h"
#include "test_helpers.h"

TEST_CASE("a ray gives back its origin and direction") {
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));

    requireVectorsEqual(ray.origin(), Vector(1, 2, 3));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}

TEST_CASE("at gives the origin for t = 0") {
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    requireVectorsEqual(ray.at(0), Vector(0, 8, 0));
}

TEST_CASE("at gives the point at distance t along the ray") {
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    requireVectorsEqual(ray.at(2), Vector(6, 0, 0));
}
