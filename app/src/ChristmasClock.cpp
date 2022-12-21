#include <stdio.h>

#include "ChristmasClock.hpp"

ChristmasClock::ChristmasClock::ChristmasClock():
    m_rec(),
    m_message() {}

int ChristmasClock::ChristmasClock::init() {

    // ir receiver setup
    const uint recInputPin = 13;     // gpio input pin
    PIO pio = pio0;                 // programable io

    if(m_rec.init(pio, recInputPin)) {
        printf("Could not initialize IR receiver\n");
        return -1;
    }

    // initialization successfull
    return 0;
}

void ChristmasClock::ChristmasClock::update() {
    // Check for new singal from ir receiver
    m_rec.update(&m_message);

    // Process ir signal
    if(m_message.isNew() && m_message.isValid()){
        printf("Got new and valid ir message (data: %s)", m_message.getData());
        m_message.markAsOld();
    } else {
        printf("No new valid message received");
    }
}