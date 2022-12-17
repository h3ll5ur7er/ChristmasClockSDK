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
    uint offset;
    if(pio_can_add_program(pio, &nec_receive_program)) {
        offset = pio_add_program(pio, &nec_receive_program);
    } else {
        return -1;
    }

    // claim an unused state machine from the provided PIO
    int state_machine = pio_claim_unused_sm(pio, true);
    if(state_machine == -1) {
        return -1;
    }

    // configure and enable the state machine
    nec_receive_program_init(pio, state_machine, offset, inputPin);

    return state_machine;
}

bool ChristmasClock::Receiver::decode_nec_frame(uint32_t frame, uint8_t *p_address, uint8_t *p_data){
    
    // split the received uint32_t data into 4x uint8_t 
    union {
        uint32_t raw;
        struct {
            uint8_t address;
            uint8_t inverted_address;
            uint8_t data;
            uint8_t inverted_data;
        };
    } f;

    f.raw = frame;

    // Check if submitted value is correct
    if (f.address != (f.inverted_address ^ 0xff) ||
        f.data != (f.inverted_data ^ 0xff)) {
            return false;
    }

    // store validated address and data
    *p_address = f.address;
    *p_data = f.data;

    return true;
}


