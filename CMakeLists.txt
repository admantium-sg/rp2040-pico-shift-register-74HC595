cmake_minimum_required(VERSION 3.12)

if (NOT EXISTS $ENV{PICO_SDK_PATH})
  message(FATAL_ERROR "Pico SDK Path not found, please set correct environment variable PICO_SDK_PATH")
endif ()

if(EXAMPLE_BUILD)
  include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
  pico_sdk_init()

  enable_language( C CXX ASM )
  add_subdirectory(./examples)
  add_subdirectory(./src)
endif()

if(TEST_BUILD)
  add_subdirectory(./src)  
  add_subdirectory(./test)
endif()

project(pico-shift-register)