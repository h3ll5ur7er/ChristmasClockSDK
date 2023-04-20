#pragma once

#include <cstdint>
#include <functional>

namespace ChristmasClock {
namespace IR{

using ReceivedIRQNECCallback_t = std::function<void(uint32_t)>;

class INECReceiver {
public:
    ~INECReceiver() = default;
    virtual int32_t ReceiveNEC() const = 0;
    virtual bool UseNECReceivedCallback(ReceivedIRQNECCallback_t nec_callback) = 0;
};
}
}