#include "ChristmasClock.hpp"
#include "ColorGRBa.hpp"
#include <iostream>

ChristmasClock::ChristmasClock::ChristmasClock() :
    _led(pio0),
    _seg(_led),
    _n(0),
    _gain(0xFF)
{
    _seg.SetGain(0x0F);
}

void ChristmasClock::ChristmasClock::Update() {
    _seg.SetNumber(_n);
    _seg.Update();
    _n++;
}
