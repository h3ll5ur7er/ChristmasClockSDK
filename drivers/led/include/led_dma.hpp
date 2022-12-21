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
// chain channel for configuring main dma channel to output from disjoint 8 word fragments of memory
#define DMA_CB_CHANNEL 1

#define DMA_CHANNEL_MASK (1u << DMA_CHANNEL)
#define DMA_CB_CHANNEL_MASK (1u << DMA_CB_CHANNEL)
#define DMA_CHANNELS_MASK (DMA_CHANNEL_MASK | DMA_CB_CHANNEL_MASK)

namespace ChristmasClock {
class LedDma {
public:
    LedDma(PIO pio);
    ~LedDma() = default;
    Color& operator[](uint32_t index);
    void init();
    void clear();
    void show();
private:
    PIO pio_;
    Color pixels_[NUM_LED] = {0};

    // posted when it is safe to output a new set of values
    static struct semaphore reset_delay_complete_sem_;
    // alarm handle for handling delay
    static alarm_id_t reset_delay_alarm_id_;

    static int64_t reset_delay_complete(alarm_id_t id, void *user_data);
    static void __isr dma_complete_handler();
};
}
