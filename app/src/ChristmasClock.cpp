#include "ChristmasClock.hpp"
#include "ColorGRBa.hpp"
#include <iostream>

namespace ChristmasClock{
    
const uint8_t ChristmasClock::_brightness[20] = { 2, 4, 5, 7, 9, 11, 14, 18, 22, 28, 35, 43, 54, 67, 84, 105, 131, 164, 204, 255 };

ChristmasClock::ChristmasClock() :
    _is_on(true),
    _vol_index(7),
    _led(pio0),
    _seg(_led),
    _countdown(180),
    _time(180)
{
    _seg.SetGain(_brightness[_vol_index]);
}

bool ChristmasClock::EvaluateEvent(IR::NECEvent event){
    switch(event){
        case(IR::NECEvent::NO_EVENT): return false;
        case(IR::NECEvent::ON_OFF):
            {
                _is_on = !_is_on;
                if(_is_on){
                    _seg.SetGain(_brightness[_vol_index]);
                }else{
                    _seg.SetGain(0x00);
                }
            }
            return false;
        case(IR::NECEvent::VOL_UP):
            {
                _vol_index++;
                if(_vol_index >= 20){
                    _vol_index = 19;
                }
                if(_is_on){
                    _seg.SetGain(_brightness[_vol_index]);
                }
            }
            return false;
        case(IR::NECEvent::VOL_DOWN): 
            {
                _vol_index--;
                if(_vol_index < 0){
                    _vol_index = 0;
                }
                if(_is_on){
                    _seg.SetGain(_brightness[_vol_index]);
                }
            }
            return false;
        case(IR::NECEvent::NUM_0): break;
        case(IR::NECEvent::NUM_1): break;
        case(IR::NECEvent::NUM_2): break;
        case(IR::NECEvent::NUM_3): break;
        case(IR::NECEvent::NUM_4): break;
        case(IR::NECEvent::NUM_5): break;
        case(IR::NECEvent::NUM_6): break;
        case(IR::NECEvent::NUM_7): break;
        case(IR::NECEvent::NUM_8): break;
        case(IR::NECEvent::NUM_9): break;
    }
    Reset();
    return true;
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
