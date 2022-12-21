#pragma once

#include "led.hpp"
#include "receiver.hpp"
#include "nec_message.hpp"

namespace ChristmasClock {
class ChristmasClock {
public:
    ChristmasClock();
    ~ChristmasClock() = default;

    // breif    setup all components
    int init();

    // brief    called by the main loop
    void update();
private:
    Receiver m_rec;                   // ir receiver
    NEC_Message m_message;            // ir message
};
}