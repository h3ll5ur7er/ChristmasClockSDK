// 
// Copyright (c) 2021 mjcross
//
// SPDX-License-Identifier: BSD-3-Clause
//
// resource: https://github.com/raspberrypi/pico-examples (17.12.2022)


#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"    // for clock_get_hz()

#include "receiver.hpp"

// import the assembled PIO state machine porgram
#include "nec_receive.pio.h"

// -------------------------------------------------------------
// Public functions

int ChristmasClock::Receiver::init(PIO pio, uint inputPin){
    
    // disapble all pull-up and pull-down on gpio pin
    gpio_disable_pulls(inputPin);

    // install program in the PIO shared instruction space
    if(pio_can_add_program(pio, &nec_receive_program)) {
        m_offset = pio_add_program(pio, &nec_receive_program);
    } else {
        return -1;
    }

    // claim an unused state machine from the provided PIO
    m_stateMachine = pio_claim_unused_sm(pio, true);
    if(m_stateMachine == -1) {
        return -1;
    }

    m_pio = pio;
    m_inputPin = inputPin;

    // configure and enable the state machine
    nec_receive_program_init(m_pio, m_stateMachine, m_offset, m_inputPin);

    return 0;
}

bool ChristmasClock::Receiver::update(NEC_Message* message)
{
    // check for new ir signal 
    if(!pio_sm_is_rx_fifo_empty(m_pio, m_stateMachine)){
       message->set(pio_sm_get(m_pio, m_stateMachine));
       return true;
    } else {
        message->markAsOld();
        return false;
    }
}


