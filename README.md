# DCCPico Common Library
DCCPico is a library that provides numerous structs and functions to help work with Digital Command Control,
a standard developed by the NMRA for controlling model trains and their associated accessories like turnouts.
This library is a work in progress. I hope to develop it into a library that can be used with the Raspberry Pi Pico and other
microcontrollers to help my own make open source command station based on a Pi Pico, similar to the DCC++ project
## Features
- Provides structs for working with DCC locomotive decoders in `DCC::Locomotive`
  - `MessageSpeedControl`: A struct that allows you to output speed and direction messages in 14 step, 28 step, and 128 step formats
  - `MessageFunctionGroup` and `MessageFunctionGroupExtended`: Provides a structs to store both types of function group instructions and turn them into DCC packets
- Provides a container for in-flight DCC packet data called `DCCMessageContainer_t`
## Installation
Although intended for use on a microcontroller, DCCPico is provided as a platform-agnostic library that you can
use with CMake, as with the Pico SDK. Simply insert `add_subdirectory(path/to/dccpico-common)` to your `CMakeLists.txt`.
## Usage Example
**NOTE**: All functions within DCCPico output their results into a `DCCMessageContainer_t`. 
This container includes a fixed-length buffer and a `size_t` field representing the raw DCC data bytes. 
It's important to understand that this buffer does **NOT** include any framing bits or the DCC preamble. 
It is your responsibility to generate and insert those elements when you're bit-banging the DCC signal or using peripherals like PIO. 
This design choice aligns with how I've structured my own command station project.

```cpp
#include "dccpico-common/dcc_locomotive.hpp" // Ensure this path is correct for your setup
using namespace DCC;

int main () {
    // create speed control message
    Locomotive::MessageSpeed speed;
    speed.isDirectionForward = true;
    speed.locomotiveAddress = 3;
    speed.speed = 127;
    
    // create container
    DCCMessageContainer_t container;
    
    // fill the buffer with a 128 speed step instruction
    speed.to128StepPacket(container);
    
    // Assuming you have a function to send the DCC packet over your hardware
    // This function would be responsible for adding preamble, start bit, and stop bit.
    // For example:
    // sendDCCPacket(msgContainer.buffer, msgContainer.size); 
    // Or if sendDCCPacket handles the container directly:
    // sendDCCPacket(msgContainer);
    
}
```
