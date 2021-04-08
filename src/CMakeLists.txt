# Fetch all files in current dir
file(GLOB FILES *.c *.h)

# build the lib<pico-shift-register>
add_library(pico-shift-register ${FILES})

option(TEST_BUILD "Build a test executable which uses the cmocka lib" OFF)

if(TEST_BUILD)
  target_compile_definitions(pico-shift-register PUBLIC -D TEST_BUILD)
  target_compile_definitions(pico-shift-register PUBLIC test)
else()
  target_link_libraries(pico-shift-register pico_stdlib)
endif(TEST_BUILD)

# IMPORTANT define where to find the files when the lib is included from a different folder!
target_include_directories(pico-shift-register PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})