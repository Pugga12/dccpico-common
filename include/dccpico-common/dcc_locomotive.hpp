#pragma once
#include <cstdint>
#include "types.hpp"

struct DCCMessageLocoSpeed {
    uint16_t locomotiveAddress;
    SpeedStepMode speedMode;
    bool isDirectionForward;
    uint8_t speed;
#ifndef DISABLE_LEGACY_PACKET_TYPES
    bool to14StepPacket(DCCMessageContainer_t& out) const;
#endif
    bool to28StepPacket(DCCMessageContainer_t& out) const;
    bool to128StepPacket(DCCMessageContainer_t& out) const;
};