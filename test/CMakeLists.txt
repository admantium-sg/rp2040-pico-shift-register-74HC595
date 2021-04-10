# Fetch all files in current dir
file(GLOB FILES *.c *.h)
add_executable(test ${FILES})

include(../cmake/cmocka.cmake)
target_link_libraries(test PRIVATE cmocka pico-shift-register)

set_target_properties(
  test
  PROPERTIES 
    OUTPUT_NAME pico_shift_register.tests
    SUFFIX ".bin"
)