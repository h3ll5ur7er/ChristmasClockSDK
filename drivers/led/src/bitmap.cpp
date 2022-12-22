#include "bitmap.hpp"

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>

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
Color Bitmap::getPixel(int x, int y) const{
    return _pixels[y * _width + x];
}

// Set the color of the pixel at (x, y)
void Bitmap::setPixel(int x, int y, Color color){
    _pixels[y * _width + x] = color;
}

std::ostream& operator<<(std::ostream& os, const Bitmap& bmp) {
    static const char base64_chars[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";

    os << "BMP" << bmp._width << "x" << bmp._height << ":";

    uint8_t* data = (uint8_t*)bmp._pixels.data();
    int size = bmp._pixels.size() *sizeof(Color);
    unsigned char char_4[4];

    int n = 0;
    for( ; (n +3) < size; n += 3){
        char_4[0] = (data[n +0] & 0xfc) >> 2;
        char_4[1] = ((data[n +0] & 0x03) << 4) + ((data[n +1] & 0xf0) >> 4);
        char_4[2] = ((data[n +1] & 0x0f) << 2) + ((data[n +2] & 0xc0) >> 6);
        char_4[3] = data[n +2] & 0x3f;

        for(int i = 0; i < 4; i++){
            os << base64_chars[char_4[i]];
        }
    }

    if(n < size){
        unsigned char char_3[3] = {0, 0, 0};
        int i = 0;
        for( ; n < size; n++){
            char_3[i] = data[n];
            i++;
        }

        char_4[0] = (char_3[0] & 0xfc) >> 2;
        char_4[1] = ((char_3[0] & 0x03) << 4) + ((char_3[1] & 0xf0) >> 4);
        char_4[2] = ((char_3[1] & 0x0f) << 2) + ((char_3[2] & 0xc0) >> 6);
        char_4[3] = char_3[2] & 0x3f;

        for(int j = 0; j < (i +1); j++){
            os << base64_chars[char_4[j]];
        }
        for( ; i < 3; i++){
            os << "=";
        }
    }

    os << "====";

    return os;
}

}