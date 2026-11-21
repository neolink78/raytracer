#include <catch2/catch_test_macros.hpp>

#include "material/material.h"
#include "test_helpers.h"

static const Material orange(Colour(1, 0.5, 0));
static const Vector normal(0, 0, -1);

TEST_CASE("a surface facing the light gets its full colour") {
    requireColoursEqual(orange.shade(normal, Vector(0, 0, -1)), Colour(1, 0.5, 0));
}

TEST_CASE("a surface tilted from the light gets darker by the cosine") {
    requireColoursEqual(orange.shade(normal, Vector(0.6, 0, -0.8)), Colour(0.8, 0.4, 0));
}

TEST_CASE("a surface grazed by the light is black") {
    requireColoursEqual(orange.shade(normal, Vector(1, 0, 0)), Colour(0, 0, 0));
}

TEST_CASE("a surface facing away from the light is black, not negative") {
    requireColoursEqual(orange.shade(normal, Vector(0, 0, 1)), Colour(0, 0, 0));
}
