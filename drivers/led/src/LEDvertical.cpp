#include "LEDvertical.hpp"

#include <iostream>
#include <cstring>

#include "pico/stdlib.h"
#include "pico/sem.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "led.pio.h"

namespace ChristmasClock {
LEDvertical::LEDvertical(PIO pio):
    pio(pio),
    //         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
    line_0  ({    1,          5,          9,             13,                     19,             23,             27,             31     } ),
    line_1  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_2  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_3  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_4  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_5  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_6  ({    1,          5,          9,             13,                     19,             23,             27,             31     } ),
    line_7  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_8  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_9  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_10 ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_11 ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_12 ({    1,          5,          9,             13,                     19,             23,             27,             31     } ),
    lines({ line_0, line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8, line_9, line_10, line_11, line_12 }),
    snake({     5,            9,             40,              44,                     77,              81,                 112,                116,
             4,                   10,    39,                      45,             76,                        82,     111,                          117,
             3,                   11,    38,                      46,             75,                        83,     110,                          118,
             2,                   12,    37,                      47,             74,                        84,     109,                          119,
             1,                   13,    36,                      48,             73,                        85,     108,                          120,
             0,                   14,    35,                      49,             72,                        86,     107,                          121,
               19,            15,            54,              50,                     91,             87,                 126,                122,
            20,                   34,    55,                      69,             92,                       106,     127,                          141,
            21,                   33,    56,                      68,             93,                       105,     128,                          140,
            22,                   32,    57,                      67,             94,                       104,     129,                          139,
            23,                   31,    58,                      66,             95,                       103,     130,                          138,
            24,                   30,    59,                      65,             96,                       102,     131,                          137,
               25,            29,            60,              64,                     97,              101,               132,                 136 }),
    pixels(NUM_LED)
{   
    int sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &led_program);
    led_program_init(pio, sm, offset, LED_PIN, LED_FREQUENCY_HZ, LED_BITS_PER_PIXEL);

    dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL);
    channel_config_set_transfer_data_size(&channel_config, DMA_SIZE_32);
    channel_config_set_read_increment(&channel_config, true);
    channel_config_set_write_increment(&channel_config, false);
    channel_config_set_dreq(&channel_config, pio_get_dreq(pio, sm, true));
    channel_config_set_irq_quiet(&channel_config, true);

    dma_channel_configure(DMA_CHANNEL, &channel_config, &pio->txf[sm], NULL, NUM_LED, false);

    dma_channel_set_irq0_enabled(DMA_CHANNEL, false);
    irq_set_enabled(DMA_IRQ_0, false);
}

void LEDvertical::ExtractPixels(const Bitmap& bmp, int offsetX, int offsetY) {
    int s = 0;
    int y = offsetY;

    for (auto & l : lines){
        for (auto x : l){
            pixels[snake[s]] = bmp(offsetX +x, y);
            s++;
        }
        y++;
    }
}

void LEDvertical::Update(const Bitmap& bmp, int offsetX, int offsetY) {
    ExtractPixels(bmp, offsetX, offsetY);
    
    dma_channel_hw_addr(DMA_CHANNEL)->al3_read_addr_trig = (uintptr_t) pixels.data();
}
}
