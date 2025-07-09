#pragma once
#include <cstdint>
#include <sys/types.h>
#include "types.hpp"

struct DCCMessageLocoSpeed {
    uint16_t locomotiveAddress;
    SpeedStepMode speedMode;
    bool isDirectionForward;
    uint8_t speed;

    ssize_t toDCCMessageBytes(uint8_t* buf, size_t bufSize);
};