cmake_minimum_required(VERSION 3.12)

OPTION(EXAMPLE_BUILD "Build all examples" OFF)
OPTION(TEST_BUILD "Build the test binary" OFF)
OPTION(DEBUG_BUILD "Build for Debug binary" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if(EXAMPLE_BUILD)
  if (NOT EXISTS $ENV{PICO_SDK_PATH})
    message(FATAL_ERROR "Pico SDK Path not found, please set correct environment variable PICO_SDK_PATH")
  endif ()

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

if(DEBUG_BUILD)
  if (NOT EXISTS $ENV{PICO_DEBUG_SDK_PATH})
    message(FATAL_ERROR "Pico Debug SDK Path not found, please set correct environment variable PICO_SDK_PATH")
  endif ()

  set(CMAKE_BUILD_TYPE=Debug)

  include($ENV{PICO_DEBUG_SDK_PATH}/pico_sdk_init.cmake)
  pico_sdk_init()
  
  enable_language(C CXX)
  add_subdirectory(./examples)
  add_subdirectory(./src)
endif()

project(pico-shift-register
  VERSION 1.0
  DESCRIPTION "RP2040 Raspberry Pico Library for Shift Registers"
  LANGUAGES C
)