#pragma once
#include <cstdint>

namespace ChristmasClock {
struct Color {
public:
    Color() = default;
    ~Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(uint32_t packed);
    uint32_t pack() const;
    static Color unpack(uint32_t packed);
    void print() const;
private:
    uint8_t b_;
    uint8_t r_;
    uint8_t g_;
    uint8_t w_ = 0; //padding
public:
    const static Color RED;
    const static Color GREEN;
    const static Color BLUE;
    const static Color YELLOW;
    const static Color CYAN;
    const static Color MAGENTA;
    const static Color WHITE;
    const static Color BLACK;
};
}