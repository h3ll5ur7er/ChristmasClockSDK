#pragma once

#include "led.hpp"
#include "LEDvertical.hpp"
#include "SevenSeg.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    void Tick();
    void Update();

    void Reset();

    std::time_t GetTime();
    void SetTime(std::time_t time);

private:
    LED _led;
    SevenSeg _seg;

    std::time_t _time;
    std::time_t _countdown;
};
}