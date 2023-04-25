#pragma once

#include <cstdint>
#include <functional>

namespace ChristmasClock {
namespace IR{

using ReceivedIRQCallback_t = std::function<void(uint32_t)>;

class IReceiver {
public:
    ~IReceiver() = default;
    virtual int32_t Receive() const = 0;
    virtual bool UseReceivedCallback(ReceivedIRQCallback_t callback) = 0;
};
}
}