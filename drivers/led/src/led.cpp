#include "led.hpp"

#include <iostream>
#include <cstring>

ChristmasClock::Color& ChristmasClock::DisplaySevenSegment::operator[](uint32_t index) {
    return pixels_[index];
}


void ChristmasClock::DisplaySevenSegment::init() {
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &led_program);
    led_program_init(pio, sm, offset, LED_PIN, LED_FREQUENCY_HZ, LED_BITS_PER_PIXEL);
}

void ChristmasClock::DisplaySevenSegment::clear() {
    std::memset(pixels_, 0, sizeof(pixels_));
}

void ChristmasClock::DisplaySevenSegment::show() {
    for (uint i = 0; i < NUM_LED; i++) {
        pio_sm_put_blocking(pio0, 0, pixels_[i].pack() << 8u);
    }
}
