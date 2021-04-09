cmake_minimum_required(VERSION 3.12)

if (NOT EXISTS $ENV{PICO_SDK_PATH})
  message(FATAL_ERROR "Pico SDK Path not found, please set correct environment variable PICO_SDK_PATH")
endif ()



if(EXAMPLE_BUILD)
  include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
  pico_sdk_init()
  enable_language(C CXX)
  add_subdirectory(./examples)
  add_subdirectory(./src)
endif()

if(TEST_BUILD)
  enable_language(C CXX)
  add_subdirectory(./src)  
  add_subdirectory(./test)
endif()

project(pico-shift-register
  VERSION 1.0
  DESCRIPTION "RP2040 Raspberry Pico Library for Shift Registers"
  LANGUAGES C
)