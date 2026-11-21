#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/vector.h"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

static void requireVectorsEqual(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

TEST_CASE("a + b sums two vectors component by component") {
    requireVectorsEqual(Vector(3, 4, 0) + Vector(4, -3, 0), Vector(7, 1, 0));
}

TEST_CASE("a + b sums the z components too") {
    requireVectorsEqual(Vector(3, 4, 1) + Vector(4, -3, 2), Vector(7, 1, 3));
}

TEST_CASE("a - b subtracts two vectors component by component") {
    requireVectorsEqual(Vector(4, 5, 0) - Vector(1, 1, 0), Vector(3, 4, 0));
}

TEST_CASE("a - b subtracts the z components too") {
    requireVectorsEqual(Vector(4, 5, 6) - Vector(1, 1, 2), Vector(3, 4, 4));
}

TEST_CASE("t * v scales every component") {
    requireVectorsEqual(2.0 * Vector(3, -4, 1), Vector(6, -8, 2));
}

TEST_CASE("the ray equation O + t * D gives the point at distance t") {
    Vector origin(0, 8, 0);
    Vector direction(3, -4, 0);
    double t = 2;

    requireVectorsEqual(origin + t * direction, Vector(6, 0, 0));
}

TEST_CASE("dot multiplies the components and adds them") {
    REQUIRE_THAT(Vector(3, 4, 0).dot(Vector(4, 3, 0)), WithinAbs(24, tolerance));
}

TEST_CASE("dot of two perpendicular vectors is zero") {
    REQUIRE_THAT(Vector(3, 4, 0).dot(Vector(4, -3, 0)), WithinAbs(0, tolerance));
}

TEST_CASE("dot uses the z components too") {
    REQUIRE_THAT(Vector(3, 4, 12).dot(Vector(4, 3, 1)), WithinAbs(36, tolerance));
}

TEST_CASE("length is the size of the vector") {
    REQUIRE_THAT(Vector(3, -4, 0).length(), WithinAbs(5, tolerance));
}

TEST_CASE("length uses the z component too") {
    REQUIRE_THAT(Vector(3, 4, 12).length(), WithinAbs(13, tolerance));
}

TEST_CASE("normalised keeps the direction and gives a length of 1") {
    requireVectorsEqual(Vector(3, -4, 0).normalised(), Vector(0.6, -0.8, 0));
}

TEST_CASE("normalised gives a length of 1, with z too") {
    REQUIRE_THAT(Vector(3, 4, 12).normalised().length(), WithinAbs(1, tolerance));
}
