#include "AppHdr.hpp"


void ChristmasClock::ChristmasClock::Init() {
    Receiver receiver;
    receiver.SampleDriverFunction();
}

int main() {
    ChristmasClock::ChristmasClock clock;
    clock.Init();
    return 0;
}
