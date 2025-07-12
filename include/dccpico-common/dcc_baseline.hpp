#pragma once
#include "dccpico-common/types.hpp"

namespace DCC {
    void buildDecoderReset(DCCMessageContainer_t& packet);
    void buildDecoderBroadcastStop(DCCMessageContainer_t& packet, bool eStop);
    void buildDecoderIdle(DCCMessageContainer_t& packet);
}