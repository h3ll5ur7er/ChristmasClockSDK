#pragma once

#include "hardware/pio.h"
#include <cstdint>

namespace ChristmasClock {
class Transmitter {
public:
    Transmitter(PIO pio);

    bool Transmit(uint32_t data);

private:
    static const int IR_PIN = 12;
    PIO _pio;
    int _sm;
};
}