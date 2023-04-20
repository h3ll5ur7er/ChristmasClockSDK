#pragma once

#include "INECReceiver.hpp"
#include "IReceiver.hpp"

#include "hardware/pio.h"
#include <cstdint>
#include <functional>

namespace ChristmasClock {
namespace IR{

class Receiver : public INECReceiver, public IReceiver {
public:
    Receiver(PIO pio);
    int32_t Receive() const override;
    int32_t ReceiveNEC() const override;

    uint32_t ReceiveRaw() const;

    bool UseReceivedCallback(ReceivedIRQCallback_t callback) override;
    bool UseNECReceivedCallback(ReceivedIRQNECCallback_t nec_callback) override;

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
}