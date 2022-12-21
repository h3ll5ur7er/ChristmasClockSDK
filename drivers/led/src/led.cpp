#include "led.hpp"

#include <iostream>
#include <cstring>

ChristmasClock::LED::LED(PIO pio):
    pio_(pio) {
}

ChristmasClock::Color& ChristmasClock::LED::operator[](uint32_t index) {
    return pixels_[index];
}


void ChristmasClock::LED::init() {
    int sm = pio_claim_unused_sm(pio_, true);
    uint offset = pio_add_program(pio_, &led_program);
    led_program_init(pio_, sm, offset, LED_PIN, LED_FREQUENCY_HZ, LED_BITS_PER_PIXEL);
}

void ChristmasClock::LED::clear() {
    std::memset(pixels_, 0, sizeof(pixels_));
}

void ChristmasClock::LED::show() {
    for (uint i = 0; i < NUM_LED; i++) {
        pio_sm_put_blocking(pio_, 0, pixels_[i].pack()<<8);
    }
}
