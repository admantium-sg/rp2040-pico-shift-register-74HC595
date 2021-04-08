# Fetch all files in current dir
file(GLOB FILES *.c *.h)
add_executable(test ${FILES})

include(../lib/cmocka.cmake)

target_compile_features(test PRIVATE c_std_99)
target_link_libraries(test PRIVATE cmocka-static pico-shift-register)

enable_testing()
add_test(NAME test COMMAND test)
