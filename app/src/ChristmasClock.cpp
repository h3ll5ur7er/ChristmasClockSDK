#include "ChristmasClock.hpp"
#include "ColorGRBa.hpp"
#include "IRErrorCorrection.hpp"
#include <iostream>

namespace ChristmasClock{

ChristmasClock::ChristmasClock() :
    _led(pio0),
    _seg(_led),
    _tx(pio0),
    _time(180),
    _delay(5)
{
    _seg.SetGain(0x0F);
}

int ChristmasClock::StartupChecks(){
    int steps = IRErrorCorrection::message_mask/ 10000;
    int threshold = steps;
    int count = 0;
    int err = 0;
    _seg.SetNumber(count);
    std::cout << "start checking, steps: " << steps << std::endl;
    for(int n = 0; n <= IRErrorCorrection::message_mask; n++){
        auto tmp = IRErrorCorrection::DifferentialEncoding(n);

        if(n != IRErrorCorrection::DifferentialDecoding(tmp)){
            std::cout << "error on: " << n << " - encodes to: " << tmp << " decodes to: " << IRErrorCorrection::DifferentialDecoding(tmp) << std::endl;
            err++;
        }

        if(n >= threshold){
            threshold += steps;
            count++;
            if(err == 0){
                _seg.SetForeground(ColorGRBa::GREEN);
            }else{
                _seg.SetForeground(ColorGRBa::RED);
            }
            _seg.SetNumber(count);
            std::cout << "progress: " << count << std::endl;
            std::cout << "debug: " << n << " - encodes to: " << tmp << " decodes to: " << IRErrorCorrection::DifferentialDecoding(tmp) << std::endl;
        }
    }
    _seg.SetNumber(err);
    std::cout << "error count: " << err << std::endl;

    return err;
}

void ChristmasClock::Update() {
    if(_time > 60){
        _seg.SetForeground(ColorGRBa::GREEN);
    }else if(_time > 30){
        _seg.SetForeground(ColorGRBa::YELLOW);
    }else{
        _seg.SetForeground(ColorGRBa::RED);
    }
    _seg.SetTime(_time);
    _tx.Transmit(_time);
    _seg.Update();

    if(_time == 0){
        if(_delay == 0){
            _time = 180;
            _delay = 5;
        }else{
            _delay--;
        }
    }else{
        _time--;
    }
}
}
