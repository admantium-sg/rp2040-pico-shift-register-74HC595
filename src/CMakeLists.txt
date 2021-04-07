# Fetch all files in current dir
file(GLOB FILES *.c *.h)

# build the lib<pico-shift-register>
add_library(pico-shift-register ${FILES})

# link additional libraries
target_link_libraries(pico-shift-register pico_stdlib)

# IMPORTANT define where to find the files when the lib is included from a different folder!
target_include_directories(pico-shift-register PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

