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

    void SetCountdown(std::time_t countdown);
    std::time_t GetTime();
    void SetTime(std::time_t time);

private:
    LED _led;
    SevenSeg _seg;

    bool _is_on;
    int _vol_index;
    bool _is_in_menu;
    int _menu_number;

    std::time_t _time;
    std::time_t _countdown;
    std::time_t _countdown_warning;
    std::time_t _countdown_finishing;

    static const uint8_t _brightness[20];

    bool EvaluateEventInMenu(IR::NECEvent event);
    int ConvertTimeToNumber(std::time_t time);
    std::time_t NumberToConvertTime(int number);
};
}