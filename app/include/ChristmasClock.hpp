#pragma once

#include "led.hpp"
#include "LEDvertical.hpp"
#include "bitmap.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    void Update();
private:
    Bitmap _bmp;
    LED _led;
    int _n;
    uint8_t _gain;
};
}