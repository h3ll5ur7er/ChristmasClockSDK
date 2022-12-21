#include "led_dma.hpp"

#include <iostream>
#include <cstring>


ChristmasClock::LedDma::LedDma(PIO pio):
    pio_(pio) {
}

ChristmasClock::Color& ChristmasClock::LedDma::operator[](uint32_t index) {
    return pixels_[index];
}


void ChristmasClock::LedDma::init() {
    int sm = pio_claim_unused_sm(pio_, true);
    uint offset = pio_add_program(pio_, &led_program);
    led_dma_program_init(pio_, sm, offset, LED_PIN, LED_FREQUENCY_HZ, LED_BITS_PER_PIXEL);

    // main DMA channel outputs 8 word fragments, and then chains back to the chain channel
    dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL);
    channel_config_set_transfer_data_size(&channel_config, DMA_SIZE_32);
    channel_config_set_read_increment(&channel_config, true);
    channel_config_set_write_increment(&channel_config, false);
    channel_config_set_dreq(&channel_config, pio_get_dreq(pio_, sm, true));
    channel_config_set_chain_to(&channel_config, DMA_CB_CHANNEL);
    channel_config_set_irq_quiet(&channel_config, true);
    dma_channel_configure(DMA_CHANNEL, &channel_config, &pio_->txf[sm], NULL, NUM_LED, false);
    
    //irq_set_exclusive_handler(DMA_IRQ_0, dma_complete_handler);
    dma_channel_set_irq0_enabled(DMA_CHANNEL, false);
    irq_set_enabled(DMA_IRQ_0, false);
}

void ChristmasClock::LedDma::clear() {
    std::memset(pixels_, 0, sizeof(pixels_));
}

void ChristmasClock::LedDma::show() {
    dma_channel_hw_addr(DMA_CHANNEL)->al3_read_addr_trig = (uintptr_t) pixels_;
}
