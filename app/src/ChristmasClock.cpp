#include "ChristmasClock.hpp"
#include <iostream>

ChristmasClock::ChristmasClock::ChristmasClock() :
    led_(pio0),
    n_(0) {
}

void ChristmasClock::ChristmasClock::Init() {
    led_.init();
    led_.clear();
    led_.show();
}

void ChristmasClock::ChristmasClock::Update() {
    led_.clear();

    auto segLen = 1;
    
    if (n_*segLen >= NUM_LED) {
        n_ = 0;
    }
    led_[n_ * segLen + 0] = Color::WHITE;
    // led_[n_ * segLen + 1] = Color::WHITE;
    // led_[n_ * segLen + 2] = Color::GREEN;
    // led_[n_ * segLen + 3] = Color::WHITE;
    // led_[n_ * segLen + 4] = Color::BLUE;
    n_++;

    led_.show();
}
