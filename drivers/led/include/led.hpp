#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>


#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "led.pio.h"
#include "led_setup.hpp"
#include "color.hpp"

namespace ChristmasClock {
class LED {
public:
    LED(PIO pio);
    ~LED() = default;
    Color& operator[](uint32_t index);
    void init();
    void clear();
    void show();
private:
    PIO pio_;
    Color pixels_[NUM_LED] = {0};
};
}
