#include "ChristmasClock.hpp"
#include <iostream>
#include <iomanip>
#include "pico/stdlib.h"

#include "ErrorCorrection.hpp"
#include "Receiver.hpp"
#include "Transmitter.hpp"
#include "NECEventMapper.hpp"

void countdown(uint n) {
    for (uint i = 0; i < n; i++) {
        std::cout << n -i << std::endl;
        sleep_ms(1000);
    }
}

void IRQCallback(uint32_t data){
    std::cout << "IRQ: Manchester encoded Data received" << std::endl;
    std::cout << "Receiving Data: 0x" << std::hex << std::setfill('0') << std::setw(8) << data << " decoded to:   0x" << std::setfill('0') << std::setw(8) << ChristmasClock::IR::ErrorCorrection::DecodeMessage(data) << std::endl;
}

int main() {
    stdio_init_all();

    countdown(4);
    
    ChristmasClock::ChristmasClock clock;
    ChristmasClock::IR::Transmitter trans(pio0);
    ChristmasClock::IR::Receiver recv(pio1);

    ChristmasClock::IR::NECEventMapper mapper(recv);

    recv.UseReceivedCallback(IRQCallback);

    int next_tick = time_us_32();
    int next_update = 0;
    while (true) {
        auto tick = time_us_32();
        if(tick >= next_tick){
            clock.Tick();
            next_tick += 1000000;

            trans.Transmit(clock.GetTime());
        }
        next_update--;
        if(next_update <= 0){
            next_update = 20;
            clock.Update();
        }
        sleep_ms(10);
        if(auto event = mapper.GetEvent(); event != ChristmasClock::IR::NECEvent::NO_EVENT){
            clock.Reset();
            next_tick = time_us_32() + 1000000;
            std::cout << "New NEC Event: " << event << std::endl;
        }
    }
    return 0;
}
