#pragma once

#include "hardware/pio.h"
#include <cstdint>

namespace ChristmasClock {
class Transmitter {
public:
    Transmitter(PIO pio);

    void Transmit(uint32_t data);

private:
    static const int IR_PIN = 12;
    PIO _pio;
    int _sm;

    static uint32_t CalculateParities(uint32_t data);
};
}