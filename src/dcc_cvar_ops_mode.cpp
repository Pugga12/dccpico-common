#include "dccpico-common/dcc_cvar_ops_mode.hpp"
#include "dccpico-common/types.hpp"
#include "dccpico-common/dcc_baseline.hpp"

namespace DCC::CVarOpsMode {
    bool CVAILongForm::writeByte(DCCMessageContainer_t &out) {
        if (cvNumber > 1023) return false; // perform input validation on the CV num
        const ssize_t addressBytesWritten = writeAddress(out.buffer, locomotiveAddress);
        if (addressBytesWritten <= 0) return false; // check if address was written successfully
        
        const uint8_t cvNumberTop = (cvNumber >> 8) & 0b11;
        uint8_t dataByte1 = 0b11101100;

    }
}