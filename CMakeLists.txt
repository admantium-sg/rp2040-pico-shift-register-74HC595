cmake_minimum_required(VERSION 3.12)

# if (NOT EXISTS $ENV{PICO_SDK_PATH})
#   message(FATAL_ERROR "Pico SDK Path not found, please set correct environment variable PICO_SDK_PATH")
# endif ()

project(pico-shift-register)

option(TEST_BUILD "Build a test executable which uses the cmocka lib" OFF)

if(TEST_BUILD)
  add_subdirectory(./src)  
  add_subdirectory(./test)
else()
  include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
  pico_sdk_init()
  add_subdirectory(./examples)
  add_subdirectory(./src)
endif()
