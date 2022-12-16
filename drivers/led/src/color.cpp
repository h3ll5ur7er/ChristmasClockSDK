#include "color.hpp"

ChristmasClock::Color::Color(uint8_t r, uint8_t g, uint8_t b):
    g_(g),
    r_(r),
    b_(b) { }

ChristmasClock::Color::Color(uint32_t packed):
    g_((packed >> 16) & 0xff),
    r_((packed >> 8) & 0xff),
    b_(packed & 0xff) { }

uint32_t ChristmasClock::Color::pack() const{
    return (g_ << 16) | (r_ << 8) | b_;
}

static ChristmasClock::Color unpack(uint32_t packed){
    return ChristmasClock::Color((packed >> 8) & 0xff, (packed >> 16) & 0xff, packed & 0xff);
}


const ChristmasClock::Color ChristmasClock::Color::RED     (0xff, 0x00, 0x00);
const ChristmasClock::Color ChristmasClock::Color::GREEN   (0x00, 0xff, 0x00);
const ChristmasClock::Color ChristmasClock::Color::BLUE    (0x00, 0x00, 0xff);
const ChristmasClock::Color ChristmasClock::Color::YELLOW  (0xff, 0xff, 0x00);
const ChristmasClock::Color ChristmasClock::Color::CYAN    (0x00, 0xff, 0xff);
const ChristmasClock::Color ChristmasClock::Color::MAGENTA (0xff, 0x00, 0xff);
const ChristmasClock::Color ChristmasClock::Color::WHITE   (0xff, 0xff, 0xff);
const ChristmasClock::Color ChristmasClock::Color::BLACK   (0x00, 0x00, 0x00);
