// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------- //
// receive //
// ------- //

#define receive_wrap_target 0
#define receive_wrap 14

static const uint16_t receive_program_instructions[] = {
            //     .wrap_target
    0xa02b, //  0: mov    x, !null                   
    0xa0c3, //  1: mov    isr, null                  
    0x2020, //  2: wait   0 pin, 0                   
    0x4001, //  3: in     pins, 1                    
    0x00c7, //  4: jmp    pin, 7                     
    0x0044, //  5: jmp    x--, 4                     
    0x0000, //  6: jmp    0                          
    0xa049, //  7: mov    y, !x                      
    0xa022, //  8: mov    x, y                       
    0x0249, //  9: jmp    x--, 9                 [2] 
    0x4001, // 10: in     pins, 1                    
    0xa022, // 11: mov    x, y                       
    0x00cf, // 12: jmp    pin, 15                    
    0x00c8, // 13: jmp    pin, 8                     
    0x004d, // 14: jmp    x--, 13                    
            //     .wrap
    0x0051, // 15: jmp    x--, 17                    
    0x0000, // 16: jmp    0                          
    0x00cf, // 17: jmp    pin, 15                    
    0x0008, // 18: jmp    8                          
};

#if !PICO_NO_HARDWARE
static const struct pio_program receive_program = {
    .instructions = receive_program_instructions,
    .length = 19,
    .origin = -1,
};

static inline pio_sm_config receive_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + receive_wrap_target, offset + receive_wrap);
    return c;
}

#include "hardware/clocks.h"
#include "stdio.h"
#include "stdlib.h"
static inline void receive_program_init(PIO pio, uint sm, uint offset, uint pin) {
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);
    pio_sm_config c = receive_program_get_default_config(offset);
    sm_config_set_in_shift(
        &c,
        false,          // left right
        true,           // enable autopush
        32              // autopush after 32 bits
    );
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_jmp_pin(&c, pin);
    pio_gpio_init(pio, pin);
    sm_config_set_clkdiv(&c, 1);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}

#endif

