#include "ColorBRG.hpp"
#include <iomanip>

namespace ChristmasClock {
ColorBRG::ColorBRG(uint8_t r, uint8_t g, uint8_t b)
{
    _value = (g << GREEN_SHIFT) | (r << RED_SHIFT) | (b << BLUE_SHIFT);
}

ColorBRG::ColorBRG(uint32_t packed) {
    _value = packed;
}

ColorBRG::ColorBRG(const ColorBRG& color) {
    _value = color._value;
}

std::ostream& operator<<(std::ostream& os, const ColorBRG& color) {
    os << "0x" << std::setfill('0') << std::setw(6) << std::hex << (color._value & 0xFFFFFF);
    os << std::resetiosflags(std::ios::hex) << std::setfill(' ') << std::setw(0);
    return os;
}

const ColorBRG ColorBRG::RED     (0xff, 0x00, 0x00);
const ColorBRG ColorBRG::GREEN   (0x00, 0xff, 0x00);
const ColorBRG ColorBRG::BLUE    (0x00, 0x00, 0xff);
const ColorBRG ColorBRG::YELLOW  (0xff, 0xff, 0x00);
const ColorBRG ColorBRG::CYAN    (0x00, 0xff, 0xff);
const ColorBRG ColorBRG::MAGENTA (0xff, 0x00, 0xff);
const ColorBRG ColorBRG::WHITE   (0xff, 0xff, 0xff);
const ColorBRG ColorBRG::BLACK   (0x00, 0x00, 0x00);

}