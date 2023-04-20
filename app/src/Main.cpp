#include "ChristmasClock.hpp"
#include <iostream>
#include "pico/stdlib.h"

#include "Receiver.hpp"
#include "Transmitter.hpp"

void countdown(uint n) {
    for (uint i = 0; i < n; i++) {
        std::cout << n -i << std::endl;
        sleep_ms(1000);
    }
}

void IRQCallback(const ChristmasClock::Receiver& recv){
    std::cout << "IRQ: Manchester encoded Data received" << std::endl;
    recv.Receive();
}

void IRQNECCallback(const ChristmasClock::Receiver& recv){
    std::cout << "IRQ: NEC encoded Data received" << std::endl;
}

int main() {
    stdio_init_all();

    countdown(4);
    
    ChristmasClock::ChristmasClock clock;
    ChristmasClock::Transmitter trans(pio0);
    ChristmasClock::Receiver recv(pio1);

    recv.UseReceivedCallbacks(IRQCallback);

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
        if(recv.ReceiveNEC() >= 0){
            clock.Reset();
            next_tick = time_us_32() + 1000000;
        }
    }
    return 0;
}
