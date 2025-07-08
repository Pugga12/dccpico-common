#pragma once
#include <cstdint>

/**
 * @brief A baseline three-byte DCC packet\n
 * A DCC packet that consists of one address byte, one data byte, and a checksum made by XORing the data and address bytes.
 */
struct DCCPacketBaseline {
    uint8_t address;
    uint8_t data;
    uint8_t checksum;
};

/// The basic instruction types contained in bits 1-3 of an extended packet's data byte(s)
enum InstructionType : uint8_t {
    DECODER_AND_CONSIST_CONTROL = 0b000,
    ADVANCED_OPERATION          = 0b001,
    SPEED_DIRECTION_R           = 0b010,
    SPEED_DIRECTION_F           = 0b011,
    FG_1                        = 0b100,
    FG_2                        = 0b101,
    FEATURE_EXPANSION          = 0b110,
    CV_ACCESS                   = 0b111
};

enum SpeedStepMode : uint8_t {
    MODE_14 = 0,
    MODE_28 = 1,
    MODE_128 = 2
};

struct DCCPacketExtended{
    uint8_t primaryAddress;
    uint8_t extendedAddress;          // valid only if hasExtendedAddress == true
    bool hasExtendedAddress;
    uint8_t instructionBytes[3];      // raw bytes
    uint8_t instructionLength;        // 1–3
    uint8_t xorCheck;
};
