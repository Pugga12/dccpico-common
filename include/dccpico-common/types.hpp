#pragma once
#include <cstdint>
#include <sys/types.h>
#define MAX_RAW_MESSAGE_SIZE 10

namespace DCC {
    /// The basic instruction types contained in bits 1-3 of an extended packet's data byte(s)
    enum InstructionType : uint8_t {
        DECODER_AND_CONSIST_CONTROL = 0b000,
        ADVANCED_OPERATION          = 0b001,
        SPEED_DIRECTION_R           = 0b010,
        SPEED_DIRECTION_F           = 0b011,
        FG_1                        = 0b100,
        FG_2                        = 0b101,
        FEATURE_EXPANSION           = 0b110,
        CV_ACCESS                   = 0b111
    };

    enum SpeedStepMode : uint8_t {
        MODE_14 = 0,
        MODE_28 = 1,
        MODE_128 = 2
    };

    /// struct for storing in flight DCC packet data up to a set maximum length
    struct DCCMessageContainer_t {
        uint8_t buffer[MAX_RAW_MESSAGE_SIZE] = {};
        size_t size = 0;
    };
}