#include <stdio.h>
#include "pico/stdlib.h"

#include "ChristmasClock.hpp"

int main() {
    stdio_init_all(); 

    ChristmasClock::ChristmasClock clock;
    const int state = clock.init();
    if(state != 0) {
        printf("Could not initialize clock\n");
        return state;
    }
    
    // main loop
    while(true){
        clock.update();
    }
    return -1;
}
