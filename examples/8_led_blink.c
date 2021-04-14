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

void main()
{
  ShiftRegister reg = shift_register_new((PinConfig){
    .SERIAL_PIN = 9,
    .SHIFT_REGISTER_CLOCK_PIN = 11,
    .STORAGE_REGISTER_CLOCK_PIN = 10
  });

  int switch_on = 0;

  while (true)
  {
    shift_register_write_bit(&reg, 1);
    shift_register_flush(&reg);

    sleep_ms(1050);
    switch_on++;

    if (switch_on = 8)
    {
      shift_register_reset_storage(&reg);
      sleep_ms(1050);
      switch_on = 0;
    }
  }
}