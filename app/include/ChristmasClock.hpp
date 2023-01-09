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

    std::time_t _time;
    int _delay;
};
}