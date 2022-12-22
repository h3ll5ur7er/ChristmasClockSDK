#pragma once

#include "led.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    ~ChristmasClock() = default;
    void Init();
    void Update();
private:
    Led led_;
    int n_;
};
}