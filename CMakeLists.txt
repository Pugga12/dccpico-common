cmake_minimum_required(VERSION 3.31)
project(dccpico-common)

set(CMAKE_CXX_STANDARD 20)

add_library(dccpico-common STATIC
        include/dccpico-common/types.hpp
        src/dcc_locomotive.cpp
        src/dcc_baseline.cpp
        include/dccpico-common/dcc_baseline.hpp
        include/dccpico-common/dcc_locomotive.hpp
)

target_include_directories(
        dccpico-common PUBLIC include
)