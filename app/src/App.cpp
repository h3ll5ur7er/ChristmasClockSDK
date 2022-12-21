#include <stdio.h>
#include "pico/stdlib.h"

#include "AppHdr.hpp"

#include "receiver.hpp"
#include "nec_message.hpp"


void ChristmasClock::ChristmasClock::Init() {

    // ir receiver setup
    cont uint recInputPin = 13;     // gpio input pin
    PIO pio = pio0;                 // programable io
    Receiver rec;                   // ir receiver
    NEC_Message message;            // ir message

    if(rec.init(pio, recInputPin)) {
        printf("Could not initialize IR receiver\n");
        return;
    }    

    // main loop
    while(true){

        // Check for new singal from ir receiver
        rec.update(&message);

        // Process ir signal
        if(message.isNew() && message.isValid()){
            printf("Got new and valid ir message (data: %s)", message.getData());
            message.markAsOld();
        } else {
            printf("No new valid message received");
        }
    }
}

int main() {
    stdio_init_all(); 

    ChristmasClock::ChristmasClock clock;
    clock.Init();
    return 0;
}
