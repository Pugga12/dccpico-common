//
// Created by adama on 7/8/25.
//
#include "dccpico-common/dcc_locomotive.hpp"
#include "dccpico-common/dcc_base_formats.hpp"

/**
 * @brief Generates a baseline DCC speed packet (14 or 28 speed step mode).
 *
 * This method always writes exactly 3 bytes: address, instruction, and checksum.
 *
 * - In 28-step mode: all 5 speed bits (bits 4–0) are used.
 * - In 14-step mode: only bits 3–0 are used; bit 4 is always cleared.
 *
 * @note Bit 4 is commonly used in 28-step mode to control headlights (F0). To avoid
 * unintended flicker or function activation on older 14-step decoders, this method
 * explicitly clears bit 4 when encoding in 14-step mode.
*/
static bool toBaselineMessage(uint8_t* buf, SpeedStepMode speedMode, uint8_t address, uint8_t speed, bool isDirectionForward) {
    buf[0] = address; // set byte 0 to address
    uint8_t dataByte = 0b01000000;
    if (isDirectionForward) {
        dataByte |= 0b01100000;
    }
    if (speedMode == SpeedStepMode::MODE_28) {
        dataByte |= (speed & 0x1F);
    } else if (speedMode == MODE_14) {
        dataByte |= (speed & 0x0F);
    } else {
        return false;
    }
    buf[1] = dataByte;
    buf[2] = dataByte ^ address;
    return true;
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
        // 28 speed step mode
        case MODE_28:
            if (bufSize < 3 || this->speed > 31) return -2;
            return toBaselineMessage(buf, MODE_28, this->locomotiveAddress, this->speed, this->isDirectionForward) ? 3 : -3;
        // 14 speed step mode
        case MODE_14:
            if (bufSize < 3 || this->speed > 15) return -2;
            return toBaselineMessage(buf, MODE_14, this->locomotiveAddress, this->speed, this->isDirectionForward) ? 3 : -3;
        default:
            return -4;
    }
}

