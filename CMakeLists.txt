cmake_minimum_required(VERSION 3.31)
project(dccpico-common)

set(CMAKE_CXX_STANDARD 20)
option(NO_LEGACY_PACKET_TYPES "Disable 14-step packets (obselete)" ON)
option(NO_ENCODE "Don't link encode functions" OFF)
option(NO_DECODE "Don't link decode functions" ON)

add_library(dccpico-common STATIC
        include/dccpico-common/types.hpp
        src/dcc_locomotive.cpp
        src/dcc_baseline.cpp
        include/dccpico-common/dcc_baseline.hpp
        include/dccpico-common/dcc_locomotive.hpp
        src/dcc_cvar_ops_mode.cpp
        include/dccpico-common/dcc_cvar_ops_mode.hpp
)

target_include_directories(
        dccpico-common PUBLIC include
)
