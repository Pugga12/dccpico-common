#pragma once
#include <cstdint>
#include "types.hpp"

/**
 * @brief Contains structs related to Ops Mode CV Programming, also known as "Programming on Main" (POM)
 * @see [NMRA Standard 9.2.1, Extended Instructions](https://www.nmra.org/sites/default/files/standards/sandrp/DCC/S/s-9.2.1_dcc_extended_packet_formats.pdf), Section 2.3.7 - CV Access Instruction
 * @see [NMRA Standard 9.2.2](https://www.nmra.org/sites/default/files/standards/sandrp/DCC/S/s-9.2.2_decoder_cvs_2012.07.pdf) for a list of CVs
 */
namespace DCC::CVarOpsMode {
    struct CVAILongForm {
        uint16_t locomotiveAddress = 0; // The locomotive address to which the CV access applies
        uint16_t cvNumber = 0;           // The CV number to read or write
        uint8_t cvValue = 0;            // The value to write to the CV (if writing)

        bool writeByte(DCCMessageContainer_t &out);
        bool verifyByte(DCCMessageContainer_t &out);
        bool manipulateBit(DCCMessageContainer_t &out, bool setBit, uint8_t bitPosition);
    };
}