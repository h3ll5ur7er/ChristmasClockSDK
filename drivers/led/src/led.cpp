#include "led.hpp"

#include <iostream>
#include <cstring>


ChristmasClock::Led::Led(PIO pio):
    pio_(pio) {
}

ChristmasClock::Color& ChristmasClock::Led::operator[](uint32_t index) {
    return pixels_[index];
}


void ChristmasClock::Led::init() {
    int sm = pio_claim_unused_sm(pio_, true);
    uint offset = pio_add_program(pio_, &led_program);
    led_program_init(pio_, sm, offset, LED_PIN, LED_FREQUENCY_HZ, LED_BITS_PER_PIXEL);

    dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL);
    channel_config_set_transfer_data_size(&channel_config, DMA_SIZE_32);
    channel_config_set_read_increment(&channel_config, true);
    channel_config_set_write_increment(&channel_config, false);
    channel_config_set_dreq(&channel_config, pio_get_dreq(pio_, sm, true));
    channel_config_set_irq_quiet(&channel_config, true);

    dma_channel_configure(DMA_CHANNEL, &channel_config, &pio_->txf[sm], NULL, NUM_LED, false);

    dma_channel_set_irq0_enabled(DMA_CHANNEL, false);
    irq_set_enabled(DMA_IRQ_0, false);
}

void ChristmasClock::Led::clear() {
    std::memset(pixels_, 0, sizeof(pixels_));
}

void ChristmasClock::Led::show() {
    dma_channel_hw_addr(DMA_CHANNEL)->al3_read_addr_trig = (uintptr_t) pixels_;
}
