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
#include "color.hpp"


const uint32_t LED_PIN = 16;
const uint32_t NUM_LED = 15;
//const uint32_t NUM_LED = 142;
const uint32_t LED_FREQUENCY_HZ = 800 * 1000;
const uint32_t LED_BITS_PER_PIXEL = 24;

#define DMA_CHANNEL 0

namespace ChristmasClock {
class Led {
public:
    Led(PIO pio);
    Color& operator[](uint32_t index);
    void init();
    void clear();
    void show();
private:
    PIO pio_;
    Color pixels_[NUM_LED] = {0};
};
}
