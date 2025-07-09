#pragma once
#include <cstdint>
#include "types.hpp"

namespace DCC::Locomotive {
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
    struct MessageSpeed {
        uint16_t locomotiveAddress;
        bool isDirectionForward = true;
        uint8_t speed;
        #ifndef DISABLE_LEGACY_PACKET_TYPES
            bool to14StepPacket(DCCMessageContainer_t& out) const;
        #endif
        bool to28StepPacket(DCCMessageContainer_t& out) const;
        bool to128StepPacket(DCCMessageContainer_t& out) const;
    };

    /**
     *@brief Struct that stores DCC Function Group 1 & 2 instructions, depending on function group setting
     *
     *Supports instruction types:
     *- 100 (FG1): Controls FL/F0 and F1-F4 (functionGroup = 0)
     *- 101 (FG2): Controls up to 8 aux functions (F5-F12) selectable in two banks of four (functionGroup = 1 or 2)
     *
     *Functions are activated by setting or clearing bits in the functionBits bitmask
     */
    struct MessageFunctionGroup {
        uint16_t locomotiveAddress;
        uint8_t functionGroup;
        uint8_t functionBits;
        bool toMessageContainer(DCCMessageContainer_t& out) const;
    };

    /**
     * @brief Struct that stores a DCC Feature Expansion instruction with the F13-21 or F21-28 subinstruction
     *
     * There are only two selectable function groups in this instruction, so access to the 8 aux instructions F21-28 is provided by
     * setting a boolean field, isAuxFunction
     *
     * Functions are activated by setting or clearing bits in the functionBits bitmask
     * @note For F13-21, the command station must periodically send the instruction, or send the instruction at least twice,
     * according to NMRA Standard 9.2.1.
     */
    struct MessageFunctionGroupExtended {
        uint16_t locomotiveAddress;
        bool isAuxFunction;
        uint8_t functionGroup;
        bool toMessageContainer(DCCMessageContainer_t& out) const;
    };
}