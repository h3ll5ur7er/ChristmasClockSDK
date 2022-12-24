#include "ChristmasClock.hpp"
#include "testbmp.hpp"
#include <iostream>

ChristmasClock::ChristmasClock::ChristmasClock() :
    bmp_(521,13),
    led_(pio0),
    n_(0) 
{
    for (int i = 0; i < bmp_.getWidth(); i++) {
        for (int j = 0; j < bmp_.getHeight(); j++) {
            bmp_.setPixel(i, j, BMP521x13[bmp_.getWidth() * j + i]);
        }
    }
    std::cout << bmp_ << std::endl;
}

void ChristmasClock::ChristmasClock::Update() {
    led_.Update(bmp_, n_++);
    n_%=(521-33);
}
