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

//                                           0     1     2     3     4     5     6     7     8     9     A     b     C     d     E     F
const uint8_t SevenSeg::_bcdDecode[16] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47 };

SevenSeg::SevenSeg(LED& led, ColorGRBa color, ColorGRBa background) :
    _led(led),
    _bmp(LED::SCREEN_WIDTH, LED::SCREEN_HIGHT),
    _draw_leading_zero(false),
    _comma_drawn(false),
    _foreground(color),
    _background(background)
{
}

void SevenSeg::SetTime(std::time_t t){
    ClearPoints();

    auto s = t;

    if(t < 0){
        s = 0 -t;
        if(s > 3600){
            s /= 60;
        }
        if(_comma_drawn){
            SetPoint();
            _comma_drawn = false;
        }else{
            SetComma();
            _comma_drawn = true;
        }
    }else{
        if(s > 3600){
            s /= 60;
            SetDoublePoint();
        } else {
            SetPoint();
        }
    }

    std::time_t min = s /60;
    s = s -min *60;
    SetNumber(min *100 +s, 3);

    if(t < 0 && min < 10){
        SetNegative();
    }
}

void SevenSeg::SetNumber(int number, int minimal){
    int bcd = 0;
    for(int n = 0; n < 4; n++){
        int num = number /10;
        int m = number -num *10;
        number = num;
        bcd |= m << (4 *n);
    }
    SetBCDNumber(bcd, minimal);
}

void SevenSeg::SetBCDNumber(int number, int minimal){
    int count = 4;
    if(!_draw_leading_zero){
        int mask = 0xF000;
        while(!(number & mask) && count > 0){ count--; mask >>= 4; }
        if(count < minimal) count = minimal;
    }
    int n;
    for(n = 0; n < (4 -count); n++){
        ClearDigit(n);
        number <<= 4;
    }
    for(; n < 4; n++){
        SetDigit(n, number >> 12);
        number <<= 4;
    }
}

void SevenSeg::SetDigit(int position, int number){
    auto bcd = _bcdDecode[number & 0x0F];
    for(int n = 0; n < 7; n++){
        if((bcd & 0x40) == 0){
            setSegment(n, _offsets[position], _background);
        }else{
            setSegment(n, _offsets[position], _foreground);
        }
        bcd <<= 1;
    }
}

void SevenSeg::ClearDigit(int position){
    for(int n = 0; n < 7; n++){
        setSegment(n, _offsets[position], _background);
    }
}

void SevenSeg::SetPoint(){
    _bmp(16, 9) = _foreground;
}
void SevenSeg::SetComma(){
    _bmp(16, 6) = _foreground;
}
void SevenSeg::SetDoublePoint(){
    _bmp(16, 6) = _foreground;
    _bmp(16, 9) = _foreground;
}
void SevenSeg::ClearPoints(){
    _bmp(16, 6) = _background;
    _bmp(16, 9) = _background;
}

void SevenSeg::SetNegative(){
    _bmp(2, 6) = _foreground;
    _bmp(3, 6) = _foreground;
    _bmp(4, 6) = _foreground;
}
void SevenSeg::ClearNegative(){
    _bmp(2, 6) = _background;
    _bmp(3, 6) = _background;
    _bmp(4, 6) = _background;
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
