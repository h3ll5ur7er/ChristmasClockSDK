#include "nec_message.hpp"

void ChristmasClock::NEC_Message::set(uint32_t raw) {
    // Split raw message into its four components
    union {
        uint32_t raw;
        struct {
            uint8_t address;
            uint8_t address_inverted;
            uint8_t data;
            uint8_t data_inverted;
        };
    } f;

    f.raw = raw;

    m_raw = f.raw;
    m_address = f.address;
    m_address_inverted = f.address_inverted;
    m_data = f.data;
    m_data_inverted = f.data_inverted;

    m_isNew = true;
}

const uint8_t ChristmasClock::NEC_Message::getAddress() {
    return m_address; 
}

const uint8_t ChristmasClock::NEC_Message::getData() {
    return m_data;
}

void ChristmasClock::NEC_Message::markAsOld() {
    m_isNew = false;
}

bool ChristmasClock::NEC_Message::isValid() {
    return NEC_Message::validate(m_address, m_address_inverted, m_data, m_data_inverted);
}

const bool ChristmasClock::NEC_Message::isNew() {
    return m_isNew;
}

bool ChristmasClock::NEC_Message::validate(
    const uint8_t& address, const uint8_t& address_inverted, 
    const uint8_t& data, const uint8_t& data_inverted) {
        return (address == (address_inverted ^  0xff) &&
            data == (data_inverted ^ 0xff));
}