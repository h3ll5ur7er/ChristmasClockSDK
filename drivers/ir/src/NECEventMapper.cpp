#include "NECEventMapper.hpp"

#include "ErrorCorrection.hpp"
#include <functional>
#include <iostream>
#include <iomanip>

namespace ChristmasClock {
namespace IR{

NECEventMapper::NECEventMapper(const INECReceiver& receiver) :
    _receiver(receiver)
{
    addTerratecCodes(_event_lookup);
    addDVBTCodes    (_event_lookup);
    addSamsungCodes (_event_lookup);
}

NECEvent NECEventMapper::GetEvent() const{
    auto data = _receiver.ReceiveNEC();
    if(data < 0){
        return NECEvent::NO_EVENT;
    }

    auto search = (uint16_t)(data & 0x0000FFFF);
    if(auto event = _event_lookup.find(search); event != _event_lookup.end()){
        return event->second;
    }
    std::cout << "Receiving NEC Data: 0x" << std::hex << std::setfill('0') << std::setw(4) << search << std::endl;
    return NECEvent::UNKNOWN;
}

/// Macro that prints the case name to the stream.
#define PRINT_ENUM_IN_SWITCH_CASE(name) \
  case NECEvent::name: \
    stream << #name; \
    break

std::ostream& operator<<(std::ostream& stream, const NECEvent &event) {
    switch(event){
        PRINT_ENUM_IN_SWITCH_CASE(NO_EVENT);
        PRINT_ENUM_IN_SWITCH_CASE(UNKNOWN);
        PRINT_ENUM_IN_SWITCH_CASE(ON_OFF);
        PRINT_ENUM_IN_SWITCH_CASE(MUTE);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_0);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_1);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_2);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_3);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_4);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_5);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_6);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_7);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_8);
        PRINT_ENUM_IN_SWITCH_CASE(NUM_9);
        default:
            stream << "Unknown NECEvent: " + std::to_string(static_cast<int>(event));
    }
    return stream;
}

void NECEventMapper::addTerratecCodes(std::map<uint16_t, NECEvent>& lookup){
   lookup[0x140c] = NECEvent::NUM_0;
   lookup[0x1402] = NECEvent::NUM_1;
   lookup[0x1403] = NECEvent::NUM_2;
   lookup[0x1404] = NECEvent::NUM_3;
   lookup[0x1405] = NECEvent::NUM_4;
   lookup[0x1406] = NECEvent::NUM_5;
   lookup[0x1407] = NECEvent::NUM_6;
   lookup[0x1408] = NECEvent::NUM_7;
   lookup[0x1409] = NECEvent::NUM_8;
   lookup[0x140a] = NECEvent::NUM_9;
   lookup[0x1401] = NECEvent::ON_OFF;
   lookup[0x141d] = NECEvent::MUTE;
}
void NECEventMapper::addDVBTCodes(std::map<uint16_t, NECEvent>& lookup){
   lookup[0x0012] = NECEvent::NUM_0;
   lookup[0x0009] = NECEvent::NUM_1;
   lookup[0x001d] = NECEvent::NUM_2;
   lookup[0x001f] = NECEvent::NUM_3;
   lookup[0x000d] = NECEvent::NUM_4;
   lookup[0x0019] = NECEvent::NUM_5;
   lookup[0x001b] = NECEvent::NUM_6;
   lookup[0x0011] = NECEvent::NUM_7;
   lookup[0x0015] = NECEvent::NUM_8;
   lookup[0x0017] = NECEvent::NUM_9;
   lookup[0x004d] = NECEvent::ON_OFF;
   lookup[0x0016] = NECEvent::MUTE;
}
void NECEventMapper::addSamsungCodes(std::map<uint16_t, NECEvent>& lookup){
   lookup[0x0711] = NECEvent::NUM_0;
   lookup[0x0704] = NECEvent::NUM_1;
   lookup[0x0705] = NECEvent::NUM_2;
   lookup[0x0706] = NECEvent::NUM_3;
   lookup[0x0708] = NECEvent::NUM_4;
   lookup[0x0709] = NECEvent::NUM_5;
   lookup[0x070a] = NECEvent::NUM_6;
   lookup[0x070c] = NECEvent::NUM_7;
   lookup[0x070d] = NECEvent::NUM_8;
   lookup[0x070e] = NECEvent::NUM_9;
   lookup[0x0702] = NECEvent::ON_OFF;
   lookup[0x070f] = NECEvent::MUTE;
}

}
}