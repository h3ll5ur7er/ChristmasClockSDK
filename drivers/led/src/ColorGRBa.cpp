#include "ColorGRBa.hpp"
#include <iomanip>

namespace ChristmasClock {
ColorGRBa::ColorGRBa(uint8_t r, uint8_t g, uint8_t b)
{
    _value = (g << GREEN_SHIFT) | (r << RED_SHIFT) | (b << BLUE_SHIFT);
}

ColorGRBa::ColorGRBa(uint32_t packed) {
    _value = packed;
}

ColorGRBa::ColorGRBa(const ColorGRBa& color) {
    _value = color._value;
}

std::ostream& operator<<(std::ostream& os, const ColorGRBa& color) {
    os << "0x" << std::setfill('0') << std::setw(8) << std::hex << (color._value & 0xFFFFFF);
    os << std::resetiosflags(std::ios::hex) << std::setfill(' ') << std::setw(0);
    return os;
}

const ColorGRBa ColorGRBa::RED     (0xff, 0x00, 0x00);
const ColorGRBa ColorGRBa::GREEN   (0x00, 0xff, 0x00);
const ColorGRBa ColorGRBa::BLUE    (0x00, 0x00, 0xff);
const ColorGRBa ColorGRBa::YELLOW  (0xff, 0xff, 0x00);
const ColorGRBa ColorGRBa::ORANGE  (0xff, 0xa5, 0x00);
const ColorGRBa ColorGRBa::CYAN    (0x00, 0xff, 0xff);
const ColorGRBa ColorGRBa::MAGENTA (0xff, 0x00, 0xff);
const ColorGRBa ColorGRBa::WHITE   (0xff, 0xff, 0xff);
const ColorGRBa ColorGRBa::BLACK   (0x00, 0x00, 0x00);

}