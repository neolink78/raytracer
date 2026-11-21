#include <catch2/catch_test_macros.hpp>

#include "vector.h"

TEST_CASE("a + b sums two vectors component by component") {
    Vector a(3, 4, 0);
    Vector b(4, -3, 0);

    Vector sum = a + b;

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 0);
}

TEST_CASE("a + b sums the z components too") {
    Vector a(3, 4, 1);
    Vector b(4, -3, 2);

    Vector sum = a + b;

    REQUIRE(sum.x() == 7);
    REQUIRE(sum.y() == 1);
    REQUIRE(sum.z() == 3);
}

TEST_CASE("a - b subtracts two vectors component by component") {
    Vector a(4, 5, 0);
    Vector b(1, 1, 0);

    Vector difference = a - b;

    REQUIRE(difference.x() == 3);
    REQUIRE(difference.y() == 4);
    REQUIRE(difference.z() == 0);
}

TEST_CASE("a - b subtracts the z components too") {
    Vector a(4, 5, 6);
    Vector b(1, 1, 2);

    Vector difference = a - b;

    REQUIRE(difference.x() == 3);
    REQUIRE(difference.y() == 4);
    REQUIRE(difference.z() == 4);
}
