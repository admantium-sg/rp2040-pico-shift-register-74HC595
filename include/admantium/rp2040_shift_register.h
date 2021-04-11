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

/* Structs */

typedef struct PinConfig
{
  uint8_t SERIAL_PIN;
  uint8_t SHIFT_REGISTER_CLOCK_PIN;
  uint8_t STORAGE_REGISTER_CLOCK_PIN;
} PinConfig;

typedef struct ShiftRegister
{
  uint8_t SERIAL_PIN;
  uint8_t SHIFT_REGISTER_CLOCK_PIN;
  uint8_t STORAGE_REGISTER_CLOCK_PIN;

  bool serial_pin_state;
  uint8_t register_state;

  bool (*write_bit)(struct ShiftRegister *, bool);
  bool (*write_bitmask)(struct ShiftRegister *, uint8_t);
  bool (*flush_shift_register)(struct ShiftRegister *);
  bool (*reset_shift_register)(struct ShiftRegister *);
  bool (*reset_storage_register)(struct ShiftRegister *);
  char *(*print_shift_register)(struct ShiftRegister *);
} ShiftRegister;

/* Constructors */

ShiftRegister shift_register_new(PinConfig);

/* External API */

bool shift_register_write_bit(ShiftRegister *, bool);
bool shift_register_write_bitmask(ShiftRegister *, uint8_t);
bool shift_register_flush(ShiftRegister *);
bool shift_register_reset(ShiftRegister *);
bool shift_register_reset_storage(ShiftRegister *);
char *shift_register_print(ShiftRegister *);
