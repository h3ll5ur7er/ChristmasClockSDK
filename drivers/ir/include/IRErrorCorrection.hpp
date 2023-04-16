#pragma once

#include <cstdint>

namespace ChristmasClock {
class IRErrorCorrection {
public:
    static const int max_message_bits = 24;
    static const uint32_t message_mask = 0x00FFFFFF;

    static const int32_t parity0_error_mask = 0x80000000;

    static const int32_t nec_error_mask = parity0_error_mask;

    static uint32_t EncodeNECMessage(uint16_t data);
    static int32_t DecodeNECMessage(uint32_t data);
    static int32_t DecodeSamsungMessage(uint32_t data);

    static uint32_t EncodeMessage(uint32_t data);
    static int32_t DecodeMessage(uint32_t data);

    static uint32_t DifferentialEncoding(uint32_t data);
    static uint32_t DifferentialDecoding(uint32_t data);

private:
    static uint32_t DisperseDatabits(uint32_t data);
    static uint32_t CollectDatabits(uint32_t data);

    static uint32_t AddParityBits(uint32_t data);
    static uint32_t AddParityBit0(uint32_t data);

    static bool CheckParityBit0(uint32_t data);
};
}