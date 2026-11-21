#pragma once

#include <vector>

#include "colour/colour.h"

class Image {
  public:
    Image(int width, int height);

    int width() const;
    int height() const;

    Colour pixel(int column, int row) const;
    void setPixel(int column, int row, const Colour& colour);

  private:
    int index(int column, int row) const;

    int _width;
    int _height;
    std::vector<Colour> _pixels;
};
