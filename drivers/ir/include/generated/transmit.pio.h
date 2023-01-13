// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// -------- //
// transmit //
// -------- //

#define transmit_wrap_target 0
#define transmit_wrap 11

#define transmit_cycles 14

static const uint16_t transmit_program_instructions[] = {
            //     .wrap_target
    0x6021, //  0: out    x, 1            side 0     
    0xf04c, //  1: set    y, 12           side 1     
    0xa042, //  2: nop                    side 0     
    0x1082, //  3: jmp    y--, 2          side 1     
    0xae42, //  4: nop                    side 0 [14]
    0x0d20, //  5: jmp    !x, 0           side 0 [13]
    0xae42, //  6: nop                    side 0 [14]
    0xed4c, //  7: set    y, 12           side 0 [13]
    0xa042, //  8: nop                    side 0     
    0x1088, //  9: jmp    y--, 8          side 1     
    0x6021, // 10: out    x, 1            side 0     
    0x1026, // 11: jmp    !x, 6           side 1     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program transmit_program = {
    .instructions = transmit_program_instructions,
    .length = 12,
    .origin = -1,
};

static inline pio_sm_config transmit_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + transmit_wrap_target, offset + transmit_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}

#include "hardware/clocks.h"
static inline void transmit_program_init(PIO pio, uint sm, uint offset, uint pin, float freq) {
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    pio_sm_config c = transmit_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_shift(&c, false, true, 32);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    int cycles_per_bit = 2;
    float div = clock_get_hz(clk_sys) / (freq * cycles_per_bit);
    sm_config_set_clkdiv(&c, div);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}

#endif
