#include "IRErrorCorrection.hpp"

namespace ChristmasClock {

uint32_t IRErrorCorrection::EncodeMessage(uint32_t data){
    data &= message_mask;
    data <<= 2;

    data = DisperseDatabits(data);
    data = AddParityBits(data);
    data = AddParityBit0(data);

    return data >> 2;
}

uint32_t IRErrorCorrection::DecodeMessage(uint32_t data){
    data <<= 2;

    // TODO: Error Correction

    data = CollectDatabits(data);

    return (data >> 2) & message_mask;
}

uint32_t IRErrorCorrection::AddParityBit0(uint32_t data){
    auto tmp = data ^ (data << 16);
    tmp ^= (tmp << 8);
    tmp ^= (tmp << 4);
    tmp ^= (tmp << 2);
    tmp ^= (tmp << 1);

    return data | (tmp & 0x80000000);
}

uint32_t IRErrorCorrection::AddParityBits(uint32_t data){
    auto h1 = data ^ (data << 8);
    auto h2 = h1 ^ (h1 >> 16);
    auto h3 = (h2 ^ ((data >> 16) & 0x000000FF)) & 0x00FFFFFF;
    auto h4 = (h3 ^ (h3 << 16)) & 0x0FFFFFFF;
    auto h5 = h4 ^ (h4 << 4);

    auto P1 = h5 ^(h5 << 2);
    data |= (P1 & (0x01 << 14)) << 14;

    auto P4_8_16 = P1 ^(P1 << 1);
    data |= (P4_8_16 & (0x01 << 31)) >> 4;
    data |= (P4_8_16 & (0x01 << 23));
    data |= (P4_8_16 & (0x01 << 7)) << 8;

    auto P2 = h5 ^ (h5 << 1);
    data |= (P2 & (0x01 << 13)) << 16;

    return data;
}


uint32_t IRErrorCorrection::DisperseDatabits(uint32_t data){
    return data      & 0x00007FFC
         | data << 1 & 0x007F0000
         | data << 2 & 0x07000000
         | data << 3 & 0x10000000;
}

uint32_t IRErrorCorrection::CollectDatabits(uint32_t data){
    return  data & 0x00007FFC
         | (data & 0x007F0000) >> 1
         | (data & 0x07000000) >> 2
         | (data & 0x10000000) >> 3;
}

}