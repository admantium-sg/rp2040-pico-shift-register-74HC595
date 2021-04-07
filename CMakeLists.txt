cmake_minimum_required(VERSION 3.12)

# if (NOT EXISTS $ENV{PICO_SDK_PATH})
#   message(FATAL_ERROR "Pico SDK Path not found, please set correct environment variable PICO_SDK_PATH")
# endif ()

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
pico_sdk_init()

project(pico-shift-register)

add_subdirectory(./src)
add_subdirectory(./examples)

# if(EXAMPLE_BUILD)
#   add_subdirectory(./src)
#   add_subdirectory(./test)
# else
  
# endif