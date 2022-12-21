#pragma once

#include "led.hpp"
#include "led_dma.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    ~ChristmasClock() = default;
    void Init();
    void Update();
private:
    LED led_;
    // LedDma led_;
    int n_;
};
}