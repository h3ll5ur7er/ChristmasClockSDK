#pragma once
#include <cstdint>
#include <iostream>

#define RED_MASK    0x00FF0000
#define RED_SHIFT   16
#define GREEN_MASK  0xFF000000
#define GREEN_SHIFT 24
#define BLUE_MASK   0x0000FF00
#define BLUE_SHIFT  8

namespace ChristmasClock {
struct ColorGRBa {
public:
    ColorGRBa() = default;
    ColorGRBa(uint8_t r, uint8_t g, uint8_t b);
    ColorGRBa(uint32_t packed);
    ColorGRBa(const ColorGRBa& color);

    uint8_t GetRed()   { return (_value & RED_MASK) >> RED_SHIFT; }
    uint8_t GetGreen() { return (_value & GREEN_MASK) >> GREEN_SHIFT; }
    uint8_t GetBlue()  { return (_value & BLUE_MASK) >> BLUE_SHIFT; }
    void SetRed(uint8_t red)     { _value = (_value & ~RED_MASK) | (red << RED_SHIFT); }
    void SetGreen(uint8_t green) { _value = (_value & ~GREEN_MASK) | (green << GREEN_SHIFT); }
    void SetBlue(uint8_t blue)   { _value = (_value & ~BLUE_MASK) | (blue << BLUE_SHIFT); }

    operator uint32_t() const { return this->_value; }
    ColorGRBa& operator+=(const ColorGRBa& addor) { _value += addor._value; return *this; }
    ColorGRBa& operator<<=(int shift) { _value <<= shift; return *this; }

    friend std::ostream& operator<<(std::ostream& os, const ColorGRBa& color);

private:
    uint32_t _value;

public:
    const static ColorGRBa RED;
    const static ColorGRBa GREEN;
    const static ColorGRBa BLUE;
    const static ColorGRBa YELLOW;
    const static ColorGRBa CYAN;
    const static ColorGRBa MAGENTA;
    const static ColorGRBa WHITE;
    const static ColorGRBa BLACK;
};
}