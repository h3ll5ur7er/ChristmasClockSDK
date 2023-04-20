#pragma once

#include "hardware/pio.h"
#include <cstdint>
#include <functional>

namespace ChristmasClock {
class Receiver {

using ReceivedIRQCallback_t = std::function<void(const Receiver&)>;
using ReceivedIRQNECCallback_t = std::function<void(const Receiver&)>;

public:
    Receiver(PIO pio);
    int32_t Receive() const;
    int32_t ReceiveNEC() const;

    uint32_t ReceiveRaw() const;

    bool UseReceivedCallbacks(ReceivedIRQCallback_t callback);
    bool UseNECReceivedCallback(ReceivedIRQNECCallback_t nec_callback);

private:
    static const int IR_PIN = 13;
    PIO _pio;
    int _sm = -1;
    int _sm_nec = -1;

    ReceivedIRQCallback_t _callback;
    ReceivedIRQNECCallback_t _nec_callback;

    bool RegisterAsIRQHandler();
    void IRQHandler();
    static void PIOIRQHandler0();
    static void PIOIRQHandler1();
    static Receiver* _interrupt_handler0_class;
    static Receiver* _interrupt_handler1_class;
};
}