#include "led.hpp"

#include <iostream>
#include <cstring>
#include <functional>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "led.pio.h"
#include "base64.hpp"

namespace ChristmasClock {
LED::LED(PIO pio):
    pio(pio),
    //         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
    line_0  ({    1, 2, 3, 4, 5,          9, 10, 11, 12, 13,                     19, 20, 21, 22, 23,             27, 28, 29, 30, 31     } ),
    line_1  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_2  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_3  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_4  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_5  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_6  ({    1, 2, 3, 4, 5,          9, 10, 11, 12, 13,         16,         19, 20, 21, 22, 23,             27, 28, 29, 30, 31     } ),
    line_7  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_8  ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_9  ({ 0,                6,    8,                    14,     16,     18,                     24,     26,                     32 } ),
    line_10 ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_11 ({ 0,                6,    8,                    14,             18,                     24,     26,                     32 } ),
    line_12 ({    1, 2, 3, 4, 5,          9, 10, 11, 12, 13,                     19, 20, 21, 22, 23,             27, 28, 29, 30, 31     } ),
    lines({ line_0, line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8, line_9, line_10, line_11, line_12 }),
    //       0, 1,  2,  3,  4,  5,  6, 7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,    24, 25,  26,  27,  28,  29,  30,  31, 32
    snake({     5,  6,  7,  8,  9,            40, 41, 42, 43, 44,                     77, 78, 79, 80, 81,                 112, 113, 114, 115, 116,
             4,                    10,    39,                     45,             76,                        82,     111,                         117,
             3,                    11,    38,                     46,             75,                        83,     110,                         118,
             2,                    12,    37,                     47,             74,                        84,     109,                         119,
             1,                    13,    36,                     48,             73,                        85,     108,                         120,
             0,                    14,    35,                     49,             72,                        86,     107,                         121,
               19, 18, 17, 16, 15,            54, 53, 52, 51, 50,         70,         91, 90, 89, 88, 87,                 126, 125, 124, 123, 122,
            20,                    34,    55,                     69,             92,                       106,     127,                         141,
            21,                    33,    56,                     68,             93,                       105,     128,                         140,
            22,                    32,    57,                     67,     71,     94,                       104,     129,                         139,
            23,                    31,    58,                     66,             95,                       103,     130,                         138,
            24,                    30,    59,                     65,             96,                       102,     131,                         137,
               25, 26, 27, 28, 29,            60, 61, 62, 63, 64,                     97, 98, 99, 100, 101,               132, 133, 134, 135, 136 }),
    pixels(NUM_LED),
    pixels_org(NUM_LED),
    _gain(0xFF)
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

void LED::ExtractPixels(const Bitmap& bmp, int offsetX, int offsetY) {
    int s = 0;
    int y = offsetY;

    for (auto & l : lines){
        for (auto x : l){
            pixels_org[snake[s]] = bmp(offsetX +x, y);
            s++;
        }
        y++;
    }
}

void LED::SetGain(uint8_t gain){
    _gain = gain;
}

void LED::ApplyGain(){
    for(int n = 0; n < NUM_LED; n++){
        pixels[n] = pixels_org[n] *_gain;
    }
}

void LED::Update(const Bitmap& bmp, int offsetX, int offsetY) {
    ExtractPixels(bmp, offsetX, offsetY);
    
    if(_gain == 0xFF){
        dma_channel_hw_addr(DMA_CHANNEL)->al3_read_addr_trig = (uintptr_t) pixels_org.data();
    }else{
        ApplyGain();
        dma_channel_hw_addr(DMA_CHANNEL)->al3_read_addr_trig = (uintptr_t) pixels.data();
    }
}

std::ostream& operator<<(std::ostream& os, const LED& led) {
    os << "7SEG:";

    uint8_t* data = (uint8_t*)led.pixels.data();
    if(led._gain == 0xFF){
        data = (uint8_t*)led.pixels_org.data();
    }
    int size = led.pixels.size() *sizeof(ColorGRBa);

    base64::toStream(os, data, size);

    os << "====";

    return os;
}


}
