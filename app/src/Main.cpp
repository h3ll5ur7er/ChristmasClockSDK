#include "ChristmasClock.hpp"
#include <iostream>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    ChristmasClock::ChristmasClock clock;

    while (true) {
        auto tick = time_us_32();
        clock.Update();
        auto tock = time_us_32();
        // std::cout<<"update took " << tock-tick << "us" <<std::endl;
        sleep_ms(100);
    }
    return 0;
}
