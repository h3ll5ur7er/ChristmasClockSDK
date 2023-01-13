#pragma once

#include <cstdint>

namespace ChristmasClock {
class IRErrorCorrection {
public:
    static const int max_message_bits = 24;
    static const uint32_t message_mask = 0x00FFFFFF;

    static uint32_t EncodeMessage(uint32_t data);
    static uint32_t DecodeMessage(uint32_t data);

private:
    static uint32_t DisperseDatabits(uint32_t data);
    static uint32_t CollectDatabits(uint32_t data);

    static uint32_t AddParityBits(uint32_t data);
    static uint32_t AddParityBit0(uint32_t data);
};
}