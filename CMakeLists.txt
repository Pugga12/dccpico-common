cmake_minimum_required(VERSION 3.31)
project(dccpico-common)

set(CMAKE_CXX_STANDARD 20)

add_library(dccpico-common STATIC
        src/DCCProtocol.cpp)

target_include_directories(
        dccpico-common PUBLIC include
)