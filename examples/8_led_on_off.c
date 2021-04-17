/* 
* ---------------------------------------
* Copyright (c) Sebastian Günther 2021  |
*                                       |    
* devcon@admantium.com                  |    
*                                       | 
* SPDX-License-Identifier: BSD-3-Clause | 
* ---------------------------------------
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>
#include <admantium/pico/shift_register_74HC595.h>

#define LED_BUILTIN 25

void main()
{
  stdio_init_all();

	gpio_init(LED_BUILTIN);
	gpio_set_dir(LED_BUILTIN, GPIO_OUT);
  gpio_put(LED_BUILTIN, 1);

	puts("Starting\n");
 
  ShiftRegister reg = shift_register_new((PinConfig){
    .SERIAL_PIN = 9,
    .SHIFT_REGISTER_CLOCK_PIN = 11,
    .STORAGE_REGISTER_CLOCK_PIN = 10
  });

  while(true) {
    printf("Switch on single LED\n");
    sleep_ms(2050);

    shift_register_write_bit(&reg, 1);
    shift_register_flush(&reg);

    printf("Switch on LED row 1\n");
    sleep_ms(2050);
    shift_register_reset_storage(&reg);
    shift_register_write_bitmask(&reg, 0b10101010);
    shift_register_flush(&reg);

    printf("Switch on LED row 2\n");
    sleep_ms(2050);
    shift_register_reset_storage(&reg);
    shift_register_write_bitmask(&reg, 0b01010101);
    shift_register_flush(&reg);

    printf("Reset all LEDs\n");
    sleep_ms(2050);
    shift_register_reset_storage(&reg);
  }
}