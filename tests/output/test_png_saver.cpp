#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <string>
#include <vector>

#include <lodepng.h>

#include "output/png_saver.h"

TEST_CASE("PngSaver writes every pixel as red, green and blue bytes, row by row") {
    Image image(2, 2);
    image.setPixel(1, 0, Colour(1, 0.5, 0));
    std::string path = (std::filesystem::temp_directory_path() / "test_png_saver.png").string();

    PngSaver saver;
    saver.save(image, path);

    std::vector<unsigned char> bytes;
    unsigned width = 0;
    unsigned height = 0;
    unsigned error = lodepng::decode(bytes, width, height, path, LCT_RGB);
    REQUIRE(error == 0);
    REQUIRE(width == 2);
    REQUIRE(height == 2);

    std::vector<int> actual(bytes.begin(), bytes.end());
    std::vector<int> expected = {0, 0, 0, 255, 128, 0, 0, 0, 0, 0, 0, 0};
    REQUIRE(actual == expected);
}
