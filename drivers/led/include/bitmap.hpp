#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cstdint>

#include "ColorGRB.hpp"

namespace ChristmasClock {

class Bitmap {
public:
    Bitmap(int width, int height);

    ColorGRB& operator()(int x, int y) { return _pixels[y *_width +x]; }
    ColorGRB operator()(int x, int y) const { return _pixels[y *_width +x]; }

    // Get the width of the bitmap
    int getWidth() const;

    // Get the height of the bitmap
    int getHeight() const;

    // Get the color of the pixel at (x, y)
    ColorGRB getPixel(int x, int y) const;

    // Set the color of the pixel at (x, y)
    void setPixel(int x, int y, ColorGRB color);

    friend std::ostream& operator<<(std::ostream& os, const Bitmap& bmp);

private:
    int _width;
    int _height;
    std::vector<ColorGRB> _pixels;
};
}
