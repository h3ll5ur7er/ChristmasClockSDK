#pragma once

#include "led.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock() = default;
    ~ChristmasClock() = default;
    void Init();
    void Update();
private:
    DisplaySevenSegment display_;
    int n_;
};
}