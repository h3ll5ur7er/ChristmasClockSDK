#pragma once

#include "pico/stdlib.h"
#include <stdint.h>

namespace ChristmasClock {
class NEC_Message {
public:
    NEC_Message() = default;
    ~NEC_Message() = default;

    // brief    set new message from raw data
    // input    raw 32 ir frame
    void set(uint32_t raw);

    // return    return message address
    const uint8_t getAddress();

    // return    return message data
    const uint8_t getData();

    // breif    set message to old
    void markAsOld();

    // return   true, is message is valid
    bool isValid();

    // return   true, if new message was not marked as old
    const bool isNew();

private:
    
    // brief    validate any nec message
    static bool validate(const uint8_t& address, const uint8_t& address_inverted, 
        const uint8_t& data, const uint8_t& data_inverted);

    uint32_t m_raw = 0;
    uint8_t m_address = 0;
    uint8_t m_address_inverted = 0;
    uint8_t m_data = 0;
    uint8_t m_data_inverted = 0;
    bool m_isNew = false;
};
}