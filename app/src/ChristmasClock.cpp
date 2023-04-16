#include "ChristmasClock.hpp"
#include "ColorGRBa.hpp"
#include "IRErrorCorrection.hpp"
#include <iostream>

namespace ChristmasClock{

ChristmasClock::ChristmasClock() :
    _led(pio0),
    _seg(_led),
    _countdown(180),
    _time(180)
{
    _seg.SetGain(0x0F);
}

void ChristmasClock::Reset() {
    _time = _countdown;
}

std::time_t ChristmasClock::GetTime(){
    return _time;
}

void ChristmasClock::SetTime(std::time_t time){
    _time = time;
}

void ChristmasClock::Tick(){
    _time--;
}

void ChristmasClock::Update() {
    if(_time > 60){
        _seg.SetForeground(ColorGRBa::GREEN);
    }else if(_time > 30){
        _seg.SetForeground(ColorGRBa::ORANGE);
    }else{
        _seg.SetForeground(ColorGRBa::RED);
    }
    _seg.SetTime(_time);
    _seg.Update();
}
}
