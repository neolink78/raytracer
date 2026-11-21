#include <catch2/catch_test_macros.hpp>

#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("the ray through a single pixel leaves the eye towards the screen centre") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the ray through a single pixel works for any eye and screen centre") {
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1), 2);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

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

TEST_CASE("render draws a red plus for a sphere in front of a 5 by 3 screen") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Sphere sphere(Vector(0, 0, 6), 5, Colour(1, 0, 0));

    Image image = camera.render(sphere, 5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            bool inPlus = (column == 2) || (row == 1 && column >= 1 && column <= 3);
            Colour expected = inPlus ? Colour(1, 0, 0) : Colour(0, 0, 0);
            requireColoursEqual(image.pixel(column, row), expected);
        }
    }
}
