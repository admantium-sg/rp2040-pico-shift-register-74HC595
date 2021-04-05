/* 
* ---------------------------------------
* Copyright (c) Sebastian Günther 2021  |
*                                       |    
* devcon@admantium.com                  |    
*                                       | 
* SPDX-License-Identifier: BSD-3-Clause | 
* ---------------------------------------
*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "rp2040_shift_register.h"
#ifdef RP2040
#include "pico/stdlib.h"
#endif
#ifdef LIBTEST
#include "mocks.c"
#endif

static bool _write_bit(ShiftRegister *reg, bool b)
{
  gpio_put(reg->SERIAL_PIN, b);
  gpio_put(reg->SHIFT_REGISTER_CLOCK_PIN, 1);
  reg->serial_pin_state = b;
  (b) ? (reg->register_state += 0b10) : (reg->register_state <<= 0b01);
  gpio_put(reg->SHIFT_REGISTER_CLOCK_PIN, 0);
  gpio_put(reg->SERIAL_PIN, 0);
  return true;
}

static bool _write_bitmask(ShiftRegister *reg, u_int8_t btm)
{
  int b = 0b0000001;
  while (b <= 128)
  {
    ((b <<= 1) & btm) ? _write_bit(reg, 1) : _write_bit(reg, 0);
  }
  reg->register_state = btm;
  return true;
}

static bool _flush_shift_register(ShiftRegister *reg)
{
  gpio_put(reg->STORAGE_REGISTER_CLOCK_PIN, 1);
  gpio_put(reg->STORAGE_REGISTER_CLOCK_PIN, 0);
  return true;
}

static bool _reset_shift_register(ShiftRegister *reg)
{

  return _write_bitmask(reg, 0b0000000);
}

static bool _reset_storage_register(ShiftRegister *reg)
{
  _write_bitmask(reg, 0b0000000);
  return _flush_shift_register(reg);
}

static char *_print_shift_register(ShiftRegister *reg)
{
  char *btm = (char *)malloc(sizeof(bool) * 8);
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

/* Constructors */

ShiftRegister shift_register_new(PinConfig pc)
{
  gpio_init(pc.SERIAL_PIN);
  gpio_set_dir(pc.SERIAL_PIN, GPIO_OUT);

  gpio_init(pc.SHIFT_REGISTER_CLOCK_PIN);
  gpio_set_dir(pc.SHIFT_REGISTER_CLOCK_PIN, GPIO_OUT);

  gpio_init(pc.STORAGE_REGISTER_CLOCK_PIN);
  gpio_set_dir(pc.STORAGE_REGISTER_CLOCK_PIN, GPIO_OUT);

  ShiftRegister *reg = malloc(sizeof(ShiftRegister));

  reg->SERIAL_PIN = pc.SERIAL_PIN;
  reg->SHIFT_REGISTER_CLOCK_PIN = pc.SHIFT_REGISTER_CLOCK_PIN;
  reg->STORAGE_REGISTER_CLOCK_PIN = pc.STORAGE_REGISTER_CLOCK_PIN;

  reg->write_bit = _write_bit;
  reg->write_bitmask = _write_bitmask;
  reg->flush_shift_register = _flush_shift_register;
  reg->reset_shift_register = _reset_shift_register;
  reg->reset_storage_register = _reset_storage_register;
  reg->print_shift_register = _print_shift_register;

  return *reg;
}

/* External API */

bool shift_register_write_bit(ShiftRegister *reg, bool b)
{
  return reg->write_bit(reg, b);
}

bool shift_register_write_bitmask(ShiftRegister *reg, u_int8_t btm)
{
  return reg->write_bitmask(reg, btm);
}

bool shift_register_flush(ShiftRegister *reg)
{
  return reg->flush_shift_register(reg);
}

bool shift_register_reset(ShiftRegister *reg)
{
  return reg->reset_shift_register(reg);
}

bool shift_register_reset_storage(ShiftRegister *reg)
{
  return reg->reset_storage_register(reg);
}

char *shift_register_print(ShiftRegister *reg)
{
  return _print_shift_register(reg);
};