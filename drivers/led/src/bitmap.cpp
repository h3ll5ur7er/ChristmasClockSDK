#include "bitmap.hpp"

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>

#include "base64.hpp"

namespace ChristmasClock {
    
Bitmap::Bitmap(int width, int height) :
    _width(width),
    _height(height),
    _pixels(width *height)
{ }

// Get the width of the bitmap
int Bitmap::getWidth() const {
  return _width;
}

// Get the height of the bitmap
int Bitmap::getHeight() const {
  return _height;
}

// Get the color of the pixel at (x, y)
ColorGRBa Bitmap::getPixel(int x, int y) const{
    return _pixels[y * _width + x];
}

// Set the color of the pixel at (x, y)
void Bitmap::setPixel(int x, int y, ColorGRBa color){
    _pixels[y * _width + x] = color;
}

std::ostream& operator<<(std::ostream& os, const Bitmap& bmp) {
    os << "BMP" << bmp._width << "x" << bmp._height << ":";

    uint8_t* data = (uint8_t*)bmp._pixels.data();
    int size = bmp._pixels.size() *sizeof(ColorGRBa);

    base64::toStream(os, data, size);

    os << "====";

    return os;
}

}