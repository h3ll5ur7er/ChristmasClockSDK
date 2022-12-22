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




#pragma once

#include "bitmap.hpp"

#include <cstdint>
#include <vector>

namespace ChristmasClock {

class LED {
public:
    LED(PIO pio);

    void Update(const Bitmap& bmp, int offsetX = 0, int offsetY = 0);

private:
    static const int LED_PIN = 16;
    static const int NUM_LED = 142;
    static const int LED_FREQUENCY_HZ = 800 * 1000;
    static const int LED_BITS_PER_PIXEL = 24;

    static const int DMA_CHANNEL = 0;

    PIO pio;

    const std::vector<uint8_t> line_0, line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8, line_9, line_10, line_11, line_12;
    const std::vector<std::vector<uint8_t>> lines;

    const std::vector<uint8_t> snake;

    std::vector<Color> pixels;
    
    void ExtractPixels(const Bitmap& bmp, int offsetX, int offsetY);
};
}
