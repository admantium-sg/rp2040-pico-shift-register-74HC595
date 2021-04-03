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
#include "pico/stdlib.h"

typedef bool bit;
typedef u_int8_t bitmask;

typedef struct
{
  u_int8_t SERIAL_PIN;
  u_int8_t SHIFT_REGISTER_CLOCK_PIN;
  u_int8_t STORAGE_REGISTER_CLOCK_PIN;

  bit serial_pin_state;
  bitmask register_state;
} ShiftRegister;

bool write_bit(bit b, ShiftRegister *reg)
{
  gpio_put(reg->SERIAL_PIN, b);
  gpio_put(reg->SHIFT_REGISTER_CLOCK_PIN, 1);
  reg->serial_pin_state = b;
  (b) ? (reg->register_state += 0b10) : (reg->register_state += 0b00);
  gpio_put(reg->SHIFT_REGISTER_CLOCK_PIN, 0);
  gpio_put(reg->SERIAL_PIN, 0);
  return b;
}

bool write_bitmask(bitmask btm, ShiftRegister *reg)
{
  int b = 0b0000001;
  while (b <= 128)
  {
    ((b <<= 1) & btm) ? write_bit(1, reg) : write_bit(0, reg);
  }
  reg->register_state = btm;
  return true;
}

bool flush_shift_register(ShiftRegister *reg)
{
  gpio_put(reg->STORAGE_REGISTER_CLOCK_PIN, 1);
  gpio_put(reg->STORAGE_REGISTER_CLOCK_PIN, 0);
  return true;
}

bool reset_shift_register(ShiftRegister *reg)
{
  return write_bitmask(0b0000000, reg);
}

bool reset_strorage_register(ShiftRegister *reg)
{
  write_bitmask(0b0000000, reg);
  flush_shift_register(reg);
  return true;
}

char *print_shift_register(ShiftRegister *reg)
{
  char *btm = (char *)malloc(sizeof(bit) * 8);
  int b = 0b00000001;

  for (int i = 0; i < 8; i++)
  {
    if ((b <<= 1) & reg->register_state)
    {
      *(btm + i) = '1';
    }
    else
    {
      *(btm + i) = '0';
    }
  }
  return btm;
}

#define SERIAL_PIN 9
#define SHIFT_REGISTER_CLOCK_PIN 11
#define STORAGE_REGISTER_CLOCK_PIN 10
#define LED_BUILTIN 25

ShiftRegister reg = {SERIAL_PIN, SHIFT_REGISTER_CLOCK_PIN, STORAGE_REGISTER_CLOCK_PIN};

void blink()
{
  gpio_put(LED_BUILTIN, 1);
  sleep_ms(750);

  gpio_put(LED_BUILTIN, 0);
  sleep_ms(1050);
}

void blinkShiftRegister()
{
  write_bit(1, &reg);
  sleep_ms(750);
  flush_shift_register(&reg);
}

void unblinkShiftRegister()
{
  write_bit(0, &reg);
  sleep_ms(750);
  flush_shift_register(&reg);
}

int main(void)
{
  stdio_init_all();
  int ledSeries = 8;

  u_int8_t pins[] = {LED_BUILTIN, SERIAL_PIN, SHIFT_REGISTER_CLOCK_PIN, STORAGE_REGISTER_CLOCK_PIN};

  for (u_int8_t i = 0; i < sizeof(pins) / sizeof(pins[0]); i++)
  {
    gpio_init(pins[i]);
    gpio_set_dir(pins[i], GPIO_OUT);
  }

  while (true)
  {
    blink();
    if (ledSeries >= 0)
    {
      blinkShiftRegister();
      ledSeries--;
    }
    else if (ledSeries >= -8)
    {
      unblinkShiftRegister();
      ledSeries--;
    }
    else
    {
      ledSeries = 8;
    }
  }
}
