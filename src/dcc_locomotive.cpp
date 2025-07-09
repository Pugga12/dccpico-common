//
// Created by adama on 7/8/25.
//
#include "dccpico-common/dcc_locomotive.hpp"
#include <sys/types.h>
#include "dccpico-common/types.hpp"

static ssize_t writeAddress(uint8_t* buf, uint16_t address) {
    if (address > 127) {
        buf[0] = static_cast<uint8_t>((address >> 8) & 0x3F) | 0xC0;
        buf[1] = static_cast<uint8_t>(address & 0xFF);
        return 2;
    } else {
        buf[0] = static_cast<uint8_t>(address);
        return 1;
    }
}

namespace DCC::Locomotive {
    // MessageSpeed
    #ifndef DISABLE_LEGACY_PACKET_TYPES
        /**
         * @brief Writes a baseline, 14 speed step packet
         * @note Intended only for legacy 14-step mode; uses short (7-bit) address.
         * Modern decoders typically use 28 or 128-step modes with extended addressing.
         * This functionality can be disabled with a compiler flag
         * @param out The message container to write the bytes to
         * @return true on success, false on failure
         */
        bool MessageSpeed::to14StepPacket(DCCMessageContainer_t &out ) const {
            if (speed > 15) return false;
            if  (writeAddress(out.buffer, this->locomotiveAddress) != 1) return false;
            uint8_t address8 = out.buffer[0];
            uint8_t dataByte = 0b01000000;
            if (isDirectionForward) dataByte |= 0b00100000;
            dataByte |= (speed & 0x0F);
            out.buffer[1] = dataByte;
            out.buffer[2] = dataByte ^ address8;
            out.size = 3;
            return true;
        }
    #endif

    /**
     * @brief Writes a 28 speed step packet in the extended format.
     * @note Assumes CV29 bit 1 is set (decoder configured for 28 speed steps).
     * Generates a packet where data bit 4 is used as part of the speed value (rather than controlling F0).
     * Suitable for modern decoders that use extended addressing and support 28-step mode.
     * @param out The message container to write the generated packet bytes into.
     * @return true on success, false on failure (e.g., invalid speed or address).
     */
    bool MessageSpeed::to28StepPacket(DCCMessageContainer_t &out ) const {
        // check for invalid speed
        if (speed > 31) return false;
        // write address and store amount of bytes written
        const size_t addressBytesWritten = writeAddress(out.buffer, this->locomotiveAddress);
        if (addressBytesWritten <= 0) return false;
        uint8_t dataByte = 0b01000000;
        if (isDirectionForward) dataByte |= 0b00100000;
        dataByte |= (this->speed & 0x1F);
        // write data byte to address 1 or 2 depending on the address format
        out.buffer[addressBytesWritten] = dataByte;
        // compute checksum byte by xor'ing address and data bytes
        uint8_t checksum = 0;
        for (size_t i = 0; i < addressBytesWritten; ++i) {
            checksum ^= out.buffer[i];
        }
        checksum ^= dataByte;
        // write checksum and size into the container
        out.buffer[addressBytesWritten + 1] = checksum;
        out.size = addressBytesWritten + 2;
        return true;
    }

    /**
     * @brief Writes a 128 speed step packet in the extended format\n
     * Uses the @link ADVANCED_OPERATION(001) extended instruction type
     * @param out The message container to write the generated packet bytes into.
     * @return true on success, false on failure (e.g., invalid speed or address).
     */
    bool MessageSpeed::to128StepPacket(DCCMessageContainer_t &out) const {
        if (speed > 127) return false;
        // write address and store amount of bytes written
        const size_t addressBytesWritten = writeAddress(out.buffer, this->locomotiveAddress);
        if (addressBytesWritten <= 0) return false;
        uint8_t dataByte1 = 0b00111111;
        uint8_t dataByte2 = 0;
        if (isDirectionForward) dataByte2 |= 0b10000000;
        dataByte2 |= (this->speed & 0x7F);
        out.buffer[addressBytesWritten] = dataByte1;
        out.buffer[addressBytesWritten + 1] = dataByte2;
        uint8_t checksum = 0;
        for (size_t i = 0; i < addressBytesWritten + 2; ++i) {
            checksum ^= out.buffer[i];
        }
        out.buffer[addressBytesWritten + 2] = checksum;
        out.size = addressBytesWritten + 3;
        return true;
    }

    bool MessageFunctionGroup::toMessageContainer(DCCMessageContainer_t &out) const {

    }

    bool MessageFunctionGroupExtended::toMessageContainer(DCCMessageContainer_t &out) const {

    }
}
