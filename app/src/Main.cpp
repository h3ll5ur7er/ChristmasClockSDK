#include "ChristmasClock.hpp"
#include <iostream>

int main() {
    stdio_init_all();
    ChristmasClock::ChristmasClock clock;
    clock.Init();

    while (true) {
        std::cout<<".";
        clock.Update();
        sleep_ms(1000);
    }
    return 0;
}
