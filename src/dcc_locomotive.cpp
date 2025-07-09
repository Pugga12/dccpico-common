//
// Created by adama on 7/8/25.
//
#include "dccpico-common/dcc_locomotive.hpp"
#include "dccpico-common/types.hpp"

/**
 * @brief Internal method that creates a DCC baseline packet out of speed and direction data
 * @note This is not intended for use with extended addressing or 28 speed step mode.
 * That fancy stuff is covered in the extended format. The fourth bit (headlight) is always cleared as the speed is clamped to 0x0F
 */
static void to14StepBase(uint8_t* buf, uint8_t address, uint8_t speed, bool isDirectionForward) {
    buf[0] = address; // set byte 0 to address
    uint8_t dataByte = 0b01000000;
    if (isDirectionForward) {
        dataByte |= 0b01100000;
    }
    dataByte |= (speed & 0x0F);
    buf[1] = dataByte;
    buf[2] = dataByte ^ address;
}

static ssize_t writeAddress(uint8_t* buf, uint16_t address) {
    if (address > 127) {
        const uint8_t high = static_cast<uint8_t>((address >> 8) & 0x3F) | 0xC0;
        const uint8_t low  = static_cast<uint8_t>(address & 0xFF);
        buf[0] = high;
        buf[1] = low;
        return 2;
    } else if (address < 128) {
        buf[0] = static_cast<uint8_t>(address);
        return 1;
    }
    return -1;
}

static ssize_t to28Step(uint8_t* buf, uint16_t address, uint8_t speed, bool isDirectionForward) {
    uint8_t currentOffset = writeAddress(buf, address) - 1;
    if (currentOffset < 0) return -1; // bad address
    uint8_t dataByte = 0b01000000;
    if (isDirectionForward) dataByte|= 0b01100000;
}

/**
 * @brief Constructs a baseline or extended DCC message out of a DCCMessageLocoSpeed struct
 *
 * @param buf Pointer to the buffer where the packet data should be placed
 * @param bufSize Size of said buffer
 * @return Returns the number of bytes written or a negative number on error
 */
ssize_t DCCMessageLocoSpeed::toDCCMessageBytes(uint8_t *buf, size_t bufSize) {
    if (buf == nullptr) {
        return -1; // null pointer
    }

    switch (this->speedMode) {
        case MODE_14:
            if (bufSize < 3 || this->speed > 15 || this->locomotiveAddress > 127) return -2;
            to14StepBase(buf, this->locomotiveAddress, this->speed, this->isDirectionForward);
            return 3;
        default:
            return -4;
    }
}

