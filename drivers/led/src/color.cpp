#include "color.hpp"
#include <iostream>

ChristmasClock::Color::Color(uint8_t r, uint8_t g, uint8_t b):
    g_(g),
    r_(r),
    b_(b) { }

ChristmasClock::Color::Color(uint32_t packed) {
        Color color = *((Color*)(&packed));
        g_ = color.g_;
        r_ = color.r_;
        b_ = color.b_;
    }

uint32_t ChristmasClock::Color::pack() const{
    return *((uint32_t*)this);
    // return (g_ << 16) | (r_ << 8) | b_;
}

static ChristmasClock::Color unpack(uint32_t packed){
    return *((ChristmasClock::Color*)(&packed));
}
void ChristmasClock::Color::print() const {
    std::cout << "r:  " << (int)r_ << "\tg:  " << (int)g_ << "\tb:  " << (int)b_ << "\tpacked: " << pack() << std::hex << std::endl;
}


const ChristmasClock::Color ChristmasClock::Color::RED     (0xff, 0x00, 0x00);
const ChristmasClock::Color ChristmasClock::Color::GREEN   (0x00, 0xff, 0x00);
const ChristmasClock::Color ChristmasClock::Color::BLUE    (0x00, 0x00, 0xff);
const ChristmasClock::Color ChristmasClock::Color::YELLOW  (0xff, 0xff, 0x00);
const ChristmasClock::Color ChristmasClock::Color::CYAN    (0x00, 0xff, 0xff);
const ChristmasClock::Color ChristmasClock::Color::MAGENTA (0xff, 0x00, 0xff);
const ChristmasClock::Color ChristmasClock::Color::WHITE   (0xff, 0xff, 0xff);
const ChristmasClock::Color ChristmasClock::Color::BLACK   (0x00, 0x00, 0x00);
