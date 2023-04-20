#include "Receiver.hpp"

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/irq.h"

#include "receive.pio.h"
#include "nec_receive.pio.h"

#include "ErrorCorrection.hpp"

#include <iostream>
#include <iomanip>

namespace ChristmasClock {
namespace IR{

Receiver* Receiver::_interrupt_handler0_class = nullptr;
Receiver* Receiver::_interrupt_handler1_class = nullptr;

Receiver::Receiver(PIO pio):
    _pio(pio)
{
    if(pio_can_add_program(_pio, &receive_program)){
        uint offset = pio_add_program(_pio, &receive_program);
        _sm = pio_claim_unused_sm(_pio, true);
        receive_program_init(_pio, _sm, offset, IR_PIN);
    }else{
        std::cout << "IR Receiver Error: unable to start manchester receiver" << std::endl;
    }
    
    if(pio_can_add_program(_pio, &nec_receive_program)){
        uint offset = pio_add_program(_pio, &nec_receive_program);
        _sm_nec = pio_claim_unused_sm(_pio, true);
        nec_receive_program_init(_pio, _sm_nec, offset, IR_PIN);
    }else{
        std::cout << "IR Receiver Error: unable to start nec receiver" << std::endl;
    }
}

bool Receiver::UseReceivedCallback(ReceivedIRQCallback_t callback){
    if(_sm < 0) return false;

    _callback = callback;
     
    switch(_sm){
        case 0: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm0_rx_fifo_not_empty, true); break;
        case 1: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm1_rx_fifo_not_empty, true); break;
        case 2: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm2_rx_fifo_not_empty, true); break;
        case 3: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm3_rx_fifo_not_empty, true); break;
        default: std::cout << "IR Receiver Error: unable enable manchaster received interrupt" << std::endl;
    }

    return RegisterAsIRQHandler();
}

bool Receiver::UseNECReceivedCallback(ReceivedIRQNECCallback_t nec_callback){
    if(_sm_nec < 0) return false;

    _nec_callback = nec_callback;

    switch(_sm_nec){
        case 0: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm0_rx_fifo_not_empty, true); break;
        case 1: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm1_rx_fifo_not_empty, true); break;
        case 2: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm2_rx_fifo_not_empty, true); break;
        case 3: pio_set_irq0_source_enabled(_pio, pio_interrupt_source::pis_sm3_rx_fifo_not_empty, true); break;
        default: std::cout << "IR Receiver Error: unable enable nec received interrupt" << std::endl;
    }

    return RegisterAsIRQHandler();
}

bool Receiver::RegisterAsIRQHandler(){
    if(_pio == pio0){
        _interrupt_handler0_class = this;
        irq_set_exclusive_handler(PIO0_IRQ_0, Receiver::PIOIRQHandler0);
        irq_set_enabled(PIO0_IRQ_0, true);
    }else if(_pio == pio1){
        _interrupt_handler1_class = this;
        irq_set_exclusive_handler(PIO1_IRQ_0, Receiver::PIOIRQHandler1);
        irq_set_enabled(PIO1_IRQ_0, true);
    }else{
        std::cout << "IR Receiver Error: unable register received interrupt handler" << std::endl;
        return false;
    }
    return true;
}

void Receiver::IRQHandler(){
    if(_callback && !pio_sm_is_rx_fifo_empty(_pio, _sm)){
        _callback(pio_sm_get(_pio, _sm));
    }

    if(_nec_callback && !pio_sm_is_rx_fifo_empty(_pio, _sm_nec)){
        _nec_callback(pio_sm_get(_pio, _sm_nec));
    }
}

void Receiver::PIOIRQHandler0(){
    if(_interrupt_handler0_class == nullptr){
        irq_set_enabled(PIO0_IRQ_0, true);
        return;
    }
    _interrupt_handler0_class->IRQHandler();
}

void Receiver::PIOIRQHandler1(){
    if(_interrupt_handler1_class == nullptr){
        irq_set_enabled(PIO1_IRQ_0, true);
        return;
    }
    _interrupt_handler1_class->IRQHandler();
}

int32_t Receiver::ReceiveNEC() const{
    if(_sm_nec < 0 || pio_sm_is_rx_fifo_empty(_pio, _sm_nec)){
        return -1;
    }

    auto recv = pio_sm_get(_pio, _sm_nec);
    auto ret = ErrorCorrection::DecodeNECMessage(recv);

    if(ret < 0){
        ret = ErrorCorrection::DecodeSamsungMessage(recv);
    }
    return ret;
}

uint32_t Receiver::ReceiveRaw() const{
    if(_sm < 0 || pio_sm_is_rx_fifo_empty(_pio, _sm)){
        return -1;
    }

    return pio_sm_get(_pio, _sm);
}

int32_t Receiver::Receive() const{
    if(_sm < 0 || pio_sm_is_rx_fifo_empty(_pio, _sm)){
        return -1;
    }

    return ErrorCorrection::DecodeMessage(pio_sm_get(_pio, _sm));
}

}
}

