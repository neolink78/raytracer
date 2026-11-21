#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "colour/colour.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("a colour gives back its red, green and blue") {
    Colour colour(1, 0.5, 0);

    REQUIRE_THAT(colour.r(), WithinAbs(1, tolerance));
    REQUIRE_THAT(colour.g(), WithinAbs(0.5, tolerance));
    REQUIRE_THAT(colour.b(), WithinAbs(0, tolerance));
}

TEST_CASE("t * colour scales red, green and blue") {
    Colour scaled = 0.5 * Colour(1, 0.5, 0);

    REQUIRE_THAT(scaled.r(), WithinAbs(0.5, tolerance));
    REQUIRE_THAT(scaled.g(), WithinAbs(0.25, tolerance));
    REQUIRE_THAT(scaled.b(), WithinAbs(0, tolerance));
}
