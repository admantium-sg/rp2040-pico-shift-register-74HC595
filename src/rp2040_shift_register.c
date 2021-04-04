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
#include "rp2040_shift_register.h"

bool write_bit(ShiftRegister *reg, bit b)
{
  reg->serial_pin_state = b;
  (b) ? (reg->register_state += 0b10) : (reg->register_state <<= 0b01);
  return true;
}

bool write_bitmask(ShiftRegister *reg, bitmask btm)
{
  int b = 0b0000001;
  while (b <= 128)
  {
    ((b <<= 1) & btm) ? write_bit(reg, 1) : write_bit(reg, 0);
  }
  reg->register_state = btm;
  return true;
}

bool flush_shift_register(ShiftRegister *reg)
{
  return true;
}

bool reset_shift_register(ShiftRegister *reg)
{
  return write_bitmask(reg, 0b0000000);
}

bool reset_strorage_register(ShiftRegister *reg)
{
  write_bitmask(reg, 0b0000000);
  return flush_shift_register(reg);
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
