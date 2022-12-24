#pragma once

#include "led.hpp"
#include "bitmap.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    void Update();
private:
    Bitmap bmp_;
    LED led_;
    int n_;
};
}