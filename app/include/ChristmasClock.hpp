#pragma once

#include "led.hpp"
#include "LEDvertical.hpp"
#include "SevenSeg.hpp"
#include "Transmitter.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    void Update();

    void Reset();

private:
    LED _led;
    SevenSeg _seg;

    std::time_t _time;
};
}