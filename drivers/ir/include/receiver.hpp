// 
// Copyright (c) 2021 mjcross
//
// SPDX-License-Identifier: BSD-3-Clause
//
// resource: https://github.com/raspberrypi/pico-examples (17.12.2022)

#pragma once

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "nec_message.hpp"

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

    // brief    update message from ir recevier
    // output   message: place to store the new message
    // return   True, if new message is available
    bool update(NEC_Message* message);
private:
    PIO m_pio;
    uint m_inputPin = 0;
    uint m_offset = 0;
    int m_stateMachine = -1;

};
}