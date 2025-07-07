#pragma once
#include <cstdint>

struct __attribute__((packed)) DCCPacket {
    uint8_t* p_data;
    uint32_t length;
};
