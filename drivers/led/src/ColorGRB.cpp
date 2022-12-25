#include "ColorGRB.hpp"
#include <iomanip>

namespace ChristmasClock {
ColorGRB::ColorGRB(uint8_t r, uint8_t g, uint8_t b)
{
    _value = (g << GREEN_SHIFT) | (r << RED_SHIFT) | (b << BLUE_SHIFT);
}

ColorGRB::ColorGRB(uint32_t packed) {
    _value = packed;
}

ColorGRB::ColorGRB(const ColorGRB& color) {
    _value = color._value;
}

std::ostream& operator<<(std::ostream& os, const ColorGRB& color) {
    os << "0x" << std::setfill('0') << std::setw(6) << std::hex << (color._value & 0xFFFFFF);
    os << std::resetiosflags(std::ios::hex) << std::setfill(' ') << std::setw(0);
    return os;
}

const ColorGRB ColorGRB::RED     (0xff, 0x00, 0x00);
const ColorGRB ColorGRB::GREEN   (0x00, 0xff, 0x00);
const ColorGRB ColorGRB::BLUE    (0x00, 0x00, 0xff);
const ColorGRB ColorGRB::YELLOW  (0xff, 0xff, 0x00);
const ColorGRB ColorGRB::CYAN    (0x00, 0xff, 0xff);
const ColorGRB ColorGRB::MAGENTA (0xff, 0x00, 0xff);
const ColorGRB ColorGRB::WHITE   (0xff, 0xff, 0xff);
const ColorGRB ColorGRB::BLACK   (0x00, 0x00, 0x00);

}