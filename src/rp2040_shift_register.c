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

static bool write_bit(ShiftRegister *reg, bit b)
{
  reg->serial_pin_state = b;
  (b) ? (reg->register_state += 0b10) : (reg->register_state <<= 0b01);
  return true;
}

static bool write_bitmask(ShiftRegister *reg, bitmask btm)
{
  int b = 0b0000001;
  while (b <= 128)
  {
    ((b <<= 1) & btm) ? write_bit(reg, 1) : write_bit(reg, 0);
  }
  reg->register_state = btm;
  return true;
}

static bool flush_shift_register(ShiftRegister *reg)
{
  return true;
}

static bool reset_shift_register(ShiftRegister *reg)
{
  return write_bitmask(reg, 0b0000000);
}

static bool reset_strorage_register(ShiftRegister *reg)
{
  write_bitmask(reg, 0b0000000);
  return flush_shift_register(reg);
}

static char *print_shift_register(ShiftRegister *reg)
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

/* Constructors */

ShiftRegister shift_register_new(PinConfig pc)
{
  ShiftRegister *reg = malloc(sizeof(ShiftRegister));

  reg->SERIAL_PIN = pc.SERIAL_PIN;
  reg->SHIFT_REGISTER_CLOCK_PIN = pc.SHIFT_REGISTER_CLOCK_PIN;
  reg->STORAGE_REGISTER_CLOCK_PIN = pc.STORAGE_REGISTER_CLOCK_PIN;

  reg->write_bit = write_bit;
  reg->write_bitmask = write_bitmask;
  reg->flush_shift_register = flush_shift_register;
  reg->reset_shift_register = reset_shift_register;
  reg->reset_strorage_register = reset_strorage_register;
  reg->print_shift_register = print_shift_register;

  return *reg;
}

// ShiftRegister *shift_register_copy(ShiftRegister *reg);
// void *shift_register_free(ShiftRegister *reg);

/* External API */

bool shift_register_write_bit(ShiftRegister *reg, bit b)
{
  return reg->write_bit(reg, b);
}

bool shift_register_write_bitmask(ShiftRegister *reg, bitmask btm)
{
  return reg->write_bitmask(reg, btm);
}

bool shift_register_flush_shift_register(ShiftRegister *reg)
{
  return reg->flush_shift_register(reg);
}

bool shift_register_reset_shift_register(ShiftRegister *reg)
{
  return reg->reset_shift_register(reg);
}

bool shift_register_reset_strorage_register(ShiftRegister *reg)
{
  return reg->reset_strorage_register(reg);
}

char *shift_register_print(ShiftRegister *reg)
{
  return (print_shift_register(reg));
};