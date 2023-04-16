#pragma once

#include "hardware/pio.h"
#include <cstdint>

namespace ChristmasClock {
class Receiver {
public:
    Receiver(PIO pio);
    int32_t Receive();
    int32_t ReceiveNEC();

private:
    static const int IR_PIN = 13;
    PIO _pio;
    int _sm = -1;
    int _sm_nec = -1;
};
}