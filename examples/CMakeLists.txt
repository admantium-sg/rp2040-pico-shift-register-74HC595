# build the a concrete examples
add_executable(8_led_blink 8_led_on_off.c)

# define where to find the files for the lib <pico-shift-register>
target_link_libraries(8_led_blink 
  pico_stdlib 
  pico_stdio_usb 
  pico-shift-register
)

pico_add_extra_outputs(8_led_blink)