#include "SevenSeg.hpp"
#include "led.hpp"

namespace ChristmasClock {

const uint8_t SevenSeg::_offsets[4] = { 0, 8, 18, 26 };
const uint8_t SevenSeg::_seg0X[5] = { 1, 2, 3, 4, 5 };
const uint8_t SevenSeg::_seg0Y[5] = { 0, 0, 0, 0, 0 };

const uint8_t SevenSeg::_seg1X[5] = { 6, 6, 6, 6, 6 };
const uint8_t SevenSeg::_seg1Y[5] = { 1, 2, 3, 4, 5 };

const uint8_t SevenSeg::_seg2X[5] = { 6, 6, 6, 6, 6 };
const uint8_t SevenSeg::_seg2Y[5] = { 7, 8, 9, 10, 11 };

const uint8_t SevenSeg::_seg3X[5] = { 1, 2, 3, 4, 5 };
const uint8_t SevenSeg::_seg3Y[5] = { 12, 12, 12, 12, 12};

const uint8_t SevenSeg::_seg4X[5] = { 0, 0, 0, 0, 0 };
const uint8_t SevenSeg::_seg4Y[5] = { 7, 8, 9, 10, 11 };

const uint8_t SevenSeg::_seg5X[5] = { 0, 0, 0, 0, 0 };
const uint8_t SevenSeg::_seg5Y[5] = { 1, 2, 3, 4, 5 };

const uint8_t SevenSeg::_seg6X[5] = { 1, 2, 3, 4, 5 };
const uint8_t SevenSeg::_seg6Y[5] = { 6, 6, 6, 6, 6 };

const uint8_t* SevenSeg::_segmentsX[7] = { _seg0X, _seg1X, _seg2X, _seg3X, _seg4X, _seg5X, _seg6X };
const uint8_t* SevenSeg::_segmentsY[7] = { _seg0Y, _seg1Y, _seg2Y, _seg3Y, _seg4Y, _seg5Y, _seg6Y };

//                                0     1     2     3     4     5     6     7     8     9     A     b     C     d     E     F
const uint8_t SevenSeg::_bcdDecode[16] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47 };

SevenSeg::SevenSeg(LED& led, ColorGRBa color, ColorGRBa background) :
    _led(led),
    _bmp(LED::SCREEN_WIDTH, LED::SCREEN_HIGHT),
    _foreground(color),
    _background(background)
{
}

void SevenSeg::SetNumber(int number){
    for(int n = 3; n >= 0; n--){
        SetDigit(n, number);
        number >>= 4;
    }
}

void SevenSeg::SetDigit(int position, int number){
    auto bcd = _bcdDecode[number & 0x0F];
    for(int n = 6; n >= 0; n--){
        if((bcd & 0x01) == 0){
            setSegment(n, _offsets[position], _background);
        }else{
            setSegment(n, _offsets[position], _foreground);
        }
        bcd >>= 1;
    }
}

void SevenSeg::SetPoint(){

}
void SevenSeg::SetDoublePoint(){

}
void SevenSeg::ClearPoints(){

}

void SevenSeg::setSegment(int number, int offsetX, ColorGRBa color){
    for(int n = 0; n < 5; n++){
        _bmp(_segmentsX[number][n] +offsetX, _segmentsY[number][n]) = color;
    }
}

void SevenSeg::SetGain(uint8_t gain){
    _led.SetGain(gain);
}

void SevenSeg::Update(){
    _led.Update(_bmp);
}

}