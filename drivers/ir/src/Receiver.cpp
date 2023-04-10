#include "Receiver.hpp"

#include <iostream>
#include "pico/stdlib.h"
#include "receive.pio.h"
#include "IRErrorCorrection.hpp"

#include <iostream>
#include <iomanip>

namespace ChristmasClock {

Receiver::Receiver(PIO pio):
    _pio(pio)
{
    if(pio_can_add_program(_pio, &receive_program)){
        uint offset = pio_add_program(_pio, &receive_program);
        _sm = pio_claim_unused_sm(_pio, true);
        receive_program_init(_pio, _sm, offset, IR_PIN);
    }else{
        std::cout << "Error: unable to start receiver" << std::endl;
    }
}

int32_t Receiver::Receive(){
    if(pio_sm_is_rx_fifo_empty(_pio, _sm)){
        return -1;
    }

uint32_t ret;
while(!pio_sm_is_rx_fifo_empty(_pio, _sm)){

    auto recv = pio_sm_get(_pio, _sm);
    ret = IRErrorCorrection::DecodeMessage(recv);
    
    std::cout << "Receiving Data: 0x" << std::hex << std::setfill('0') << std::setw(8) << recv << " decoded to:   0x" << std::setfill('0') << std::setw(8) << ret << std::endl;
}
    return (int32_t)ret;
}

}

