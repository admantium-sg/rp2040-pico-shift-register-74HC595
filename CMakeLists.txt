cmake_minimum_required(VERSION 3.12)

if (NOT EXISTS $ENV{PICO_SDK_PATH})
  message(FATAL_ERROR "Pico SDK Path not found, please set correct environment variable PICO_SDK_PATH")
endif ()

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(rp2040-pico-shift-register C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(./src)