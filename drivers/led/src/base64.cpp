#include "base64.hpp"
#include <cstdint>

namespace ChristmasClock {

void base64::toStream(std::ostream& os, void* buffer, int size){
    static const char base64_chars[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";
    auto data = (uint8_t*)buffer;

    unsigned char char_4[4];
    int n = 0;
    for( ; (n +3) < size; n += 3){
        char_4[0] = (data[n +0] & 0xfc) >> 2;
        char_4[1] = ((data[n +0] & 0x03) << 4) + ((data[n +1] & 0xf0) >> 4);
        char_4[2] = ((data[n +1] & 0x0f) << 2) + ((data[n +2] & 0xc0) >> 6);
        char_4[3] = data[n +2] & 0x3f;

        for(int i = 0; i < 4; i++){
            os << base64_chars[char_4[i]];
        }
    }

    if(n < size){
        unsigned char char_3[3] = {0, 0, 0};
        int i = 0;
        for( ; n < size; n++){
            char_3[i] = data[n];
            i++;
        }

        char_4[0] = (char_3[0] & 0xfc) >> 2;
        char_4[1] = ((char_3[0] & 0x03) << 4) + ((char_3[1] & 0xf0) >> 4);
        char_4[2] = ((char_3[1] & 0x0f) << 2) + ((char_3[2] & 0xc0) >> 6);
        char_4[3] = char_3[2] & 0x3f;

        for(int j = 0; j < (i +1); j++){
            os << base64_chars[char_4[j]];
        }
        for( ; i < 3; i++){
            os << "=";
        }
    }
}

}
