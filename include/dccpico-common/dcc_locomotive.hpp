#pragma once
#include <cstdint>
#include "types.hpp"

/**
 * @brief Struct that stores a DCC speed set instruction
 *
 * This struct holds a DCC speed step instruction that can be turned into raw packet data
 * (excluding preambles and framing bits) in three different formats accepted by decoders:
 * - 14 speed step baseline packet (legacy)
 * - 28 speed step extended format (requires CV29 bit 1 to be set)
 * - 128 speed step extended format
 *
 * @warning For all formats: speed values 0 and 1 usually mean "stop" and "emergency stop";
 *          speed >= 2 are normal speed steps.
 * @note 14 speed step operation can be disabled by defining DISABLE_LEGACY_PACKET_TYPES.
 */
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