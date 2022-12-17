// 
// Copyright (c) 2021 mjcross
//
// SPDX-License-Identifier: BSD-3-Clause
//
// resource: https://github.com/raspberrypi/pico-examples (17.12.2022)

#pragma once

#include "pico/stdlib.h"
#include "hardware/pio.h"

namespace ChristmasClock {

// class which decodes IR signals in the NEC protocol
class Receiver {
public:
    Receiver() = default;
    virtual ~Receiver() = default;

    // brief    initializes infrared receiver 
    // input    pio: programmable input output
    //          input_pin: pin at which the ir signal is received
    int init(PIO pio, uint inputPin);

    // brief    decode a infrared frame using
    // note     supports the (non-extended) NEC protocol
    // input    frame: raw data
    //          p_address: pointer where to write the address of the received frame
    //          p_data: pointer where to write the data of the received frame
    // return   ture if frame is valid
    //          otherwise false
    bool decode_nec_frame(uint32_t frame, uint8_t *p_address, uint8_t *p_data);
};
}