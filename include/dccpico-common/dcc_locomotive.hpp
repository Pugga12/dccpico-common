#pragma once
#include <cstdint>
#include <sys/types.h>
#include "dcc_base_formats.hpp"

struct DCCMessageLocoSpeed {
    uint8_t locomotiveAddress;
    SpeedStepMode speedMode;
    bool isDirectionForward;
    uint8_t speed;

    ssize_t toDCCMessageBytes(uint8_t* buf, size_t bufSize);
};
