#include <catch2/catch_test_macros.hpp>

#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("the ray through the centre leaves the eye towards the screen centre") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the ray through the centre works for any eye and screen centre") {
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1), 2);

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}
