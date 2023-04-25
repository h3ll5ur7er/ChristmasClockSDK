#include "ChristmasClock.hpp"
#include "ColorGRBa.hpp"
#include <iostream>

namespace ChristmasClock{
    
const uint8_t ChristmasClock::_brightness[20] = { 2, 4, 5, 7, 9, 11, 14, 18, 22, 28, 35, 43, 54, 67, 84, 105, 131, 164, 204, 255 };

ChristmasClock::ChristmasClock() :
    _led(pio0),
    _seg(_led),
    _is_on(true),
    _vol_index(7),
    _is_in_menu(false),
    _menu_number(0),
    _countdown(180),
    _countdown_warning(60),
    _countdown_finishing(30),
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
        case(IR::NECEvent::ENTER_MENU): 
            {
                if(_is_in_menu){
                    if(_menu_number > 0){
                        SetCountdown(NumberToConvertTime(_menu_number));
                    }
                }else{
                    _menu_number = 0;
                    _seg.SetForeground(ColorGRBa::WHITE);
                    _seg.SetBCDNumber(ConvertTimeToNumber(_countdown), 3);
                    _seg.SetDoublePoint();
                    _seg.Update();
                }
                _is_in_menu = !_is_in_menu;
            }
            return false;
    }
    if(_is_in_menu) return EvaluateEventInMenu(event);
    Reset();
    return true;
}

int ChristmasClock::ConvertTimeToNumber(std::time_t time){
    int minutes = ((int)time) /60;
    int seconds = ((int)time) -(minutes *60);

    int bcd_minutes_high = minutes /10;
    int bcd_minutes_low  = minutes -(bcd_minutes_high *10);

    int bcd_seconds_high = seconds /10;
    int bcd_seconds_low  = seconds -(bcd_seconds_high *10);
    return (bcd_minutes_high << 12) | (bcd_minutes_low << 8) | (bcd_seconds_high << 4) | bcd_seconds_low;
}

std::time_t ChristmasClock::NumberToConvertTime(int number){
    int minutes = (number >> 12) * 10;
    minutes += (number >> 8) & 0x0F;

    number &= 0x00FF;
    int seconds = (number >> 4) * 10;
    seconds += number & 0x0F;

    return minutes *60 +seconds;
}

bool ChristmasClock::EvaluateEventInMenu(IR::NECEvent event){
    switch(event){
        case(IR::NECEvent::NUM_0): { _menu_number <<= 4; _menu_number |= 0; } break;
        case(IR::NECEvent::NUM_1): { _menu_number <<= 4; _menu_number |= 1; } break;
        case(IR::NECEvent::NUM_2): { _menu_number <<= 4; _menu_number |= 2; } break;
        case(IR::NECEvent::NUM_3): { _menu_number <<= 4; _menu_number |= 3; } break;
        case(IR::NECEvent::NUM_4): { _menu_number <<= 4; _menu_number |= 4; } break;
        case(IR::NECEvent::NUM_5): { _menu_number <<= 4; _menu_number |= 5; } break;
        case(IR::NECEvent::NUM_6): { _menu_number <<= 4; _menu_number |= 6; } break;
        case(IR::NECEvent::NUM_7): { _menu_number <<= 4; _menu_number |= 7; } break;
        case(IR::NECEvent::NUM_8): { _menu_number <<= 4; _menu_number |= 8; } break;
        case(IR::NECEvent::NUM_9): { _menu_number <<= 4; _menu_number |= 9; } break;
    }
    _menu_number &= 0x0000FFFF;
    _seg.SetBCDNumber(_menu_number, 3);
    return false;
}

void ChristmasClock::Reset() {
    _time = _countdown;
}

void ChristmasClock::SetCountdown(std::time_t countdown){
    _countdown = countdown;
    _countdown_warning = countdown / 3;
    _countdown_finishing = _countdown_warning / 2;
    _time = countdown;
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
    if(_is_in_menu) {
        _seg.Update();
        return;
    }
    if(_time > _countdown_warning){
        _seg.SetForeground(ColorGRBa::GREEN);
    }else if(_time > _countdown_finishing){
        _seg.SetForeground(ColorGRBa::ORANGE);
    }else{
        _seg.SetForeground(ColorGRBa::RED);
    }
    _seg.SetTime(_time);
    _seg.Update();
}
}
