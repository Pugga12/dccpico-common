#include "dccpico-common/dcc_baseline.hpp"

namespace DCC {
    /**
     * @brief Instructs decoders to reset volatile memory and return to its "power-on state"
     * 
     * **ALL** decoders will erase their volatile memory (including speed and direction data) and return to its power on state
     * 
     * Locomotive decoders with a non-zero speed will be brought to a stop. 
     * @param packet The message container to write the generated packet bytes into.
     * 
     * @note This is a baseline packet described in [NMRA Standard 9.2.](https://www.nmra.org/sites/default/files/standards/sandrp/DCC/S/s-92-2004-07.pdf)
     * DCC hardware must conform to these standards to provide minimum interoperability between different systems.
     */
    void buildDecoderReset(DCCMessageContainer_t &packet) {
        // all bytes to 0 (reset volatile memory)
        packet.buffer[0] = 0;
        packet.buffer[1] = 0;
        packet.buffer[2] = 0;
        packet.size = 3;
    }
    
    /**
     * @brief Instructs decoders operating locomotive motors to stop or immediately cut power to its motor (emergency stop).
     * 
     * The library treats this instruction as not direction-specific, so bit 5 of the data byte is cleared and bit 4 is set to ignore the direction
     * 
     * @param packet The message container to write the generated packet bytes into.
     * @param eStop If true, decoders that recieve this packet will cut power to their motor immediately instead of stopping gracefully
     * @note This is a baseline packet described in [NMRA Standard 9.2.](https://www.nmra.org/sites/default/files/standards/sandrp/DCC/S/s-92-2004-07.pdf)
     * DCC hardware must conform to these standards to provide minimum interoperability between different systems.
     */
    void buildDecoderBroadcastStop(DCCMessageContainer_t &packet, bool eStop) {
        packet.buffer[0] = 0; // address byte 0 / broadcast
        // data byte (01DC000S)
        // Set direction bit to 0, C bit to 1 to ignore direction
        uint8_t dataByte = 0b01010000;
        // set bit 0 to 1 if estop (immediately stop power to motors)
        if (eStop) dataByte |= 0b00000001;
        packet.buffer[1] = dataByte;
        packet.buffer[2] = dataByte;
        packet.size=3;
    }

    /**
     * @brief This is an idle packet. Decoders will treat this packet if it were a normal packet addressed to any other decoder
     * 
     * @param packet The message container to write the generated packet bytes into.
     * @note This is a baseline packet described in [NMRA Standard 9.2.](https://www.nmra.org/sites/default/files/standards/sandrp/DCC/S/s-92-2004-07.pdf)
     * DCC hardware must conform to these standards to provide minimum interoperability between different systems.
     */
    void buildDecoderIdle(DCCMessageContainer_t &packet) {
        // decoder idle (address and error byte set to 255)
        packet.buffer[0] = 0xFF;
        packet.buffer[1] = 0;
        packet.buffer[2] = 0xFF;
        packet.size = 3;
    }
}