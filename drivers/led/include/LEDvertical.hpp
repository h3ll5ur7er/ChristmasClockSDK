#pragma once

#include "ColorGRBa.hpp"
#include "bitmap.hpp"
#include "hardware/pio.h"

#include <cstdint>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

namespace ChristmasClock {

class LEDvertical {
public:
    LEDvertical(PIO pio);

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

    std::vector<ColorGRBa> pixels;
    
    void ExtractPixels(const Bitmap& bmp, int offsetX, int offsetY);
};
}
