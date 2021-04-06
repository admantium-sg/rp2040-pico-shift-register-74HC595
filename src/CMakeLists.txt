add_executable(rp2040-pico-shift-register-example 
  rp2040_shift_register.c
)

target_link_libraries(rp2040-pico-shift-register-example rp2040_shift_register pico_stdlib)

pico_add_extra_outputs(rp2040-pico-shift-register-example)