/* 
* ---------------------------------------
* Copyright (c) Sebastian Günther 2021  |
*                                       |    
* devcon@admantium.com                  |    
*                                       | 
* SPDX-License-Identifier: BSD-3-Clause | 
* ---------------------------------------
*/
#include <stdbool.h>
#include <stdint.h>

typedef bool bit;
typedef uint8_t bitmask;

typedef struct ShiftRegister
{
  uint8_t SERIAL_PIN;
  uint8_t SHIFT_REGISTER_CLOCK_PIN;
  uint8_t LATCH_REGISTER_CLOCK_PIN;

  bool serial_pin_state;
  uint8_t register_state;
} ShiftRegister;

bool write_bit(ShiftRegister *, bit);
bool write_bitmask(ShiftRegister *, bitmask);
bool flush_shift_register(ShiftRegister *);
bool reset_shift_register(ShiftRegister *);
bool reset_strorage_register(ShiftRegister *);
char *print_shift_register(ShiftRegister *);
