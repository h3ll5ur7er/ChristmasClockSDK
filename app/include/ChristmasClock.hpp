#pragma once

#include "led.hpp"
#include "LEDvertical.hpp"
#include "SevenSeg.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    void Update();

private:
    LED _led;
    SevenSeg _seg;

    int _n;
    uint8_t _gain;
};
}