#pragma once

#include "INECReceiver.hpp"

#include <cstdint>
#include <queue>
#include <map>

namespace ChristmasClock {
namespace IR{

enum class NECEvent{
    NO_EVENT,
    UNKNOWN,
    ON_OFF,
    MUTE,
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
};

class NECEventMapper {
public:
    NECEventMapper(const INECReceiver& receiver);

    NECEvent GetEvent() const;

private:
    const INECReceiver& _receiver;
    std::map<uint16_t, NECEvent> _event_lookup;

    void addTerratecCodes(std::map<uint16_t, NECEvent>& lookup);
    void addDVBTCodes(std::map<uint16_t, NECEvent>& lookup);
    void addSamsungCodes(std::map<uint16_t, NECEvent>& lookup);
};
}
}