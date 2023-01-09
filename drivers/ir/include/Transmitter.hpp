#pragma once

#include "hardware/pio.h"

namespace ChristmasClock {
class Transmitter {
public:
    Transmitter(PIO pio);
    void SampleDriverFunction();

private:
    PIO _pio;
};
}