#include "ChristmasClock.hpp"
#include <iostream>

void countdown(uint n) {
    for (uint i = 0; i < n; i++) {
        std::cout<<n-i<<std::endl;
        sleep_ms(1000);
    }
}

int main() {
    stdio_init_all();
    countdown(4);
    ChristmasClock::ChristmasClock clock;
    clock.Init();

    while (true) {
        auto tick = time_us_32();
        clock.Update();
        auto tock = time_us_32();
        // std::cout<<"update took " << tock-tick << "us" <<std::endl;
        sleep_ms(100);
    }
    return 0;
}