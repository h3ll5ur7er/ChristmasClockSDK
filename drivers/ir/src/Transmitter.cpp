#include "Transmitter.hpp"

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "transmit.pio.h"

#include <iostream>

namespace ChristmasClock {

Transmitter::Transmitter(PIO pio):
    _pio(pio)
{
    _sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &transmit_program);
    transmit_program_init(pio, _sm, offset, IR_PIN, 38e3);
}

void Transmitter::Transmit(uint32_t data){
    _pio->txf[_sm] = data;
}

}
