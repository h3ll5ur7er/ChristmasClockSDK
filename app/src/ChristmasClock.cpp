#include "ChristmasClock.hpp"
#include "ColorBRG.hpp"
#include <iostream>

ChristmasClock::ChristmasClock::ChristmasClock() :
    _bmp(LED::SCREEN_WIDTH *4, LED::SCREEN_HIGHT),
    _led(pio0),
    _n(0),
    _gain(0xFF)
{
    ColorBRG color = 0x0000FF;
    for(int x = 0; x < (LED::SCREEN_WIDTH *4); x++){
        for(int y = 0; y < LED::SCREEN_HIGHT; y++){
            _bmp(x, y) = color;
        }
        color <<= 1;
        if(color == 0x00){
            color = 0x0000FF;
        }
    }

    std::cout << _bmp << std::endl;
}

void ChristmasClock::ChristmasClock::Update() {
    _led.SetGain(_gain--);
    _led.Update(_bmp, _n++);
    std::cout << _led << std::endl;
    if(_n >= LED::SCREEN_WIDTH *2){
        _n = 0;
    }
}
