#pragma once
#include "dccpico-common/types.hpp"
#include <cstdint>
#include <sys/types.h>

namespace DCC {
    void buildDecoderReset(DCCMessageContainer_t& packet);
    void buildDecoderBroadcastStop(DCCMessageContainer_t& packet, bool eStop);
    void buildDecoderIdle(DCCMessageContainer_t& packet);
    ssize_t writeAddress(uint8_t* buf, uint16_t address);
}