cmake_minimum_required(VERSION 3.31)
project(dccpico-common)

set(CMAKE_CXX_STANDARD 20)

add_library(dccpico-common STATIC
        src/DCCPacket.hpp
        src/DCCProtocol.cpp)
