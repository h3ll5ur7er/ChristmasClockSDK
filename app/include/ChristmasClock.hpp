#pragma once

#include "led.hpp"
#include "LEDvertical.hpp"
#include "SevenSeg.hpp"
#include "NECEventMapper.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    void Tick();
    void Update();

    bool EvaluateEvent(IR::NECEvent event);

    void Reset();

    std::time_t GetTime();
    void SetTime(std::time_t time);

private:
    bool _is_on;
    int _vol_index;
    LED _led;
    SevenSeg _seg;

    std::time_t _time;
    std::time_t _countdown;

    static const uint8_t _brightness[20];
};
}