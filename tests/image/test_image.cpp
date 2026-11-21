#include <catch2/catch_test_macros.hpp>

#include "image/image.h"
#include "test_helpers.h"

TEST_CASE("an image knows its width and height") {
    Image image(5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("every pixel of a new image is black") {
    Image image(5, 3);

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
        }
    }
}

TEST_CASE("setting a pixel changes that pixel only") {
    Image image(5, 3);

    image.setPixel(4, 0, Colour(1, 0, 0));

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            Colour expected = (column == 4 && row == 0) ? Colour(1, 0, 0) : Colour(0, 0, 0);
            requireColoursEqual(image.pixel(column, row), expected);
        }
    }
}
