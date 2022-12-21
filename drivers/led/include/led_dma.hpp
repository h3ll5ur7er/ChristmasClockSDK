#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

#include "pico/stdlib.h"
#include "pico/sem.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "led.pio.h"
#include "led_setup.hpp"
#include "color.hpp"

// bit plane content dma channel
#define DMA_CHANNEL 0

namespace ChristmasClock {
class LedDma {
public:
    LedDma(PIO pio);
    Color& operator[](uint32_t index);
    void init();
    void clear();
    void show();
private:
    PIO pio_;
    Color pixels_[NUM_LED] = {0};
};
}
