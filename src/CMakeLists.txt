# Fetch all files in current dir
file(GLOB FILES *.c *.h)
add_library(pico-shift-register ${FILES})

if(TEST_BUILD)
  # pass -D TEST_BUILD when compiling
  target_compile_definitions(pico-shift-register PUBLIC -D TEST_BUILD)
  target_link_libraries(pico-shift-register test)
else()
  # normal build, link with pico_stdlib
  target_link_libraries(pico-shift-register pico_stdlib)
endif(TEST_BUILD)

# IMPORTANT define where to find the files when the lib is included from a different folder!
target_include_directories(pico-shift-register PUBLIC ../include)