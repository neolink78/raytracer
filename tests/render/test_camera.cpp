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

TEST_CASE("the ray through the centre pixel goes straight ahead") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the ray through the top right pixel goes right and up") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(2, 1, 1));
}

TEST_CASE("the ray through the bottom left pixel goes left and down") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(-2, -1, 1));
}
