#include "ChristmasClock.hpp"

void ChristmasClock::ChristmasClock::Init() {
    display_.init();
    display_.clear();
    display_.show();
}

void ChristmasClock::ChristmasClock::Update() {
    display_.clear();
    
    if (n_*3 >= NUM_LED) {
        n_ = 0;
    }
    display_[n_ * 3 + 0] = Color::RED;
    display_[n_ * 3 + 1] = Color::GREEN;
    display_[n_ * 3 + 2] = Color::BLUE;
    n_++;

    display_.show();
}
