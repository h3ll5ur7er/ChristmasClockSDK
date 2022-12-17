#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "receiver.hpp"

#include "AppHdr.hpp"


void ChristmasClock::ChristmasClock::Init() {

    const uint8_t LED_PIN = 25;

    // LED setup
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // ir receiver setup
    PIO pio = pio0;
    Receiver rec;

    int rx_sm = rec.init(
        pio,    // programable io
        15      // gpio input pin 
    );
    if(rx_sm == -1) {
        printf("Could not configure PIO\n");
        return;
    }

    uint8_t rx_address, rx_data;

    // main loop
    while(true){

        // let LED blink 
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);

        // check for ir input 
        while(!pio_sm_is_rx_fifo_empty(pio, rx_sm)){
            uint32_t rx_frame = pio_sm_get(pio, rx_sm);

            if(rec.decode_nec_frame(rx_frame, &rx_address, &rx_data)) {
                printf("\treceived: %02x, %02x\n", rx_address, rx_data);
            } else {
                printf("\treceived: %08x\n", rx_frame);
            }
        }
    }
}

int main() {
    stdio_init_all(); 

    ChristmasClock::ChristmasClock clock;
    clock.Init();
    return 0;
}
