#include "Transmitter.hpp"

#include "pico/stdlib.h"
#include "transmit.pio.h"
#include "IRErrorCorrection.hpp"

#include <iostream>
#include <iomanip>

namespace ChristmasClock {

Transmitter::Transmitter(PIO pio):
    _pio(pio)
{
    _sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &transmit_program);
    transmit_program_init(pio, _sm, offset, IR_PIN, 38e3);
}

bool Transmitter::Transmit(uint32_t data){
    if(pio_sm_is_tx_fifo_full(_pio, _sm)){
        return false;
    }
    auto tmp = IRErrorCorrection::EncodeMessage(data);
    pio_sm_put(_pio, _sm, tmp);
    std::cout << "Sending Data:   0x" << std::hex << std::setfill('0') << std::setw(8) << IRErrorCorrection::DifferentialEncoding(tmp) << " encoded from: 0x" << std::setfill('0') << std::setw(8) << data << std::endl;
    return true;
}

}
