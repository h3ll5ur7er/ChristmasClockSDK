#include "IRErrorCorrection.hpp"

namespace ChristmasClock {

uint32_t IRErrorCorrection::EncodeNECMessage(uint16_t data){
    uint32_t data_tmp = (((uint32_t)data) << 8) | ((uint32_t)data);
    data_tmp &= 0x00FF00FF;
    return ~data_tmp | (data_tmp << 8);
}

int32_t IRErrorCorrection::DecodeNECMessage(uint32_t data){
    uint32_t data_tmp = ~data;
    data >>= 8;
    data_tmp &= 0x00FF00FF;
    data &= 0x00FF00FF;
    int32_t err_mask = data_tmp ^ data;
    if(err_mask != 0) err_mask = nec_error_mask;
    return err_mask | ((data | (data >> 8)) & 0x0000FFFF);
}

uint32_t IRErrorCorrection::EncodeMessage(uint32_t data){
    data &= message_mask;
    data <<= 2;

    data = DisperseDatabits(data);
    data = AddParityBits(data);
    data = AddParityBit0(data);

    return DifferentialEncoding(data >> 2);
}

int32_t IRErrorCorrection::DecodeMessage(uint32_t data){
    uint32_t err_mask = 0;
    data = DifferentialDecoding(data) << 2;

    // TODO: Error Correction
    if(!CheckParityBit0(data)){
        err_mask |= parity0_error_mask;
    }
    data = CollectDatabits(data);

    return ((data >> 2) & message_mask) | err_mask;
}

bool IRErrorCorrection::CheckParityBit0(uint32_t data){
    auto tmp = data ^ (data << 16);
    tmp ^= (tmp << 8);
    tmp ^= (tmp << 4);
    tmp ^= (tmp << 2);
    tmp ^= (tmp << 1);

    return (tmp & 0x80000000) == 0;
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
    data |= (P1 & (0x01 << 14)) << 16;

    auto P4_8_16 = P1 ^ (P1 << 1);
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

uint32_t IRErrorCorrection::DifferentialEncoding(uint32_t data){
    //                                     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
    static const uint8_t start_zero[] = {  0,  1,  3,  2,  7,  6,  4,  5, 15, 14, 12, 13,  8,  9, 11, 10 };
    //static const uint8_t start_one[]  = { 15, 14, 12, 13,  8,  9, 11, 10,  0,  1,  3,  2,  7,  6,  4,  5 };

    uint32_t output = 0;
    for(int n = 0; n < 8; n++){
        auto tmp = output << 3;
        output <<= 4;
        tmp += data >> ((7 -n) *4);
        output |= (uint32_t)start_zero[tmp & 0x000F];
    }

    return output;
}

// An alternative Method to adchieve the same without addition but it takes 4 more commands for some reason
//uint32_t IRErrorCorrection::DifferentialEncoding_new(uint32_t data){
//    //                                     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
//    static const uint8_t start_zero[] = { /* last bit in stream was 0: */
//                                           0,  1,  3,  2,  7,  6,  4,  5, 15, 14, 12, 13,  8,  9, 11, 10,
//                                          /* last bit in stream was 1: */ 
//                                          15, 14, 12, 13,  8,  9, 11, 10,  0,  1,  3,  2,  7,  6,  4,  5 };
//
//    uint32_t output = 0;
//    for(int n = 0; n < 8; n++){
//        output <<= 4;
//        auto tmp = output | ((data >> ((7 -n) *4)) & 0x000F);
//        output |= (uint32_t)start_zero[tmp & 0x001F];
//    }
//
//    return output;
//}

uint32_t IRErrorCorrection::DifferentialDecoding(uint32_t data){
    //                                     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
    static const uint8_t start_zero[] = { /* last bit in stream was 0: */
                                           0,  1,  3,  2,  6,  7,  5,  4, 12, 13, 15, 14, 10, 11,  9,  8,
                                          /* last bit in stream was 1: */
                                           8,  9, 11, 10, 14, 15, 13, 12,  4,  5,  7,  6,  2,  3,  1,  0 };

    uint32_t output = 0;
    for(int n = 0; n < 8; n++){
        output <<= 4;
        auto tmp = data >> ((7 -n) *4);
        output |= (uint32_t)start_zero[tmp & 0x001F];
    }

    return output;
}

// An alternative method to adchieve the same thing
//uint32_t IRErrorCorrection::DifferentialDecoding(uint32_t data){
//    //                                     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
//    static const uint8_t start_zero[] = {  0,  1,  3,  2,  6,  7,  5,  4, 12, 13, 15, 14, 10, 11,  9,  8 };
//    static const uint8_t start_one[]  = {  8,  9, 11, 10, 14, 15, 13, 12,  4,  5,  7,  6,  2,  3,  1,  0 };
//
//    uint32_t output = 0;
//    for(int n = 0; n < 8; n++){
//        output <<= 4;
//        auto tmp = data >> ((7 -n) *4);
//        if((tmp & 0x0010) == 0){
//            output |= (uint32_t)start_zero[tmp & 0x000F];
//        }else{
//            output |= (uint32_t)start_one[tmp & 0x000F];
//        }
//    }
//
//    return output;
//}

}