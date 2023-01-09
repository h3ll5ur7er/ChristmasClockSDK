#include "Transmitter.hpp"

#include "transmit.pio.h"

#include <iostream>

namespace ChristmasClock {

Transmitter::Transmitter(PIO pio):
    _pio(pio)
{

}

void Transmitter::SampleDriverFunction() {
    std::cout<<"Sender::SampleDriverFunction()"<<std::endl;
}

}
