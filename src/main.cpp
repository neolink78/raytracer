#include <iostream>
#include <string>

#include "colour/colour.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "math/vector.h"
#include "output/png_saver.h"
#include "render/camera.h"

int main() {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Image image = camera.render(sphere, 400, 300);

    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);

    std::cout << "Saved " << path << '\n';
    return 0;
}
