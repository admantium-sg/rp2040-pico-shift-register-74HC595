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
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

typedef bool bit;
typedef u_int8_t bitmask;

typedef struct
{
  u_int8_t SERIAL_PIN;
  u_int8_t SHIFT_REGISTER_CLOCK_PIN;
  u_int8_t LATCH_REGISTER_CLOCK_PIN;

  bit serial_pin_state;
  bitmask register_state;
} ShiftRegister;

bool write_bit(bit b, ShiftRegister *reg)
{
  printf("Write Bit %d\n", b);
  reg->serial_pin_state = b;
  return b;
}

bool write_bitmask(bitmask btm, ShiftRegister *reg)
{
  reg->register_state = btm;
  int b = 0b0000001;
  while (b <= 128)
  {
    ((b <<= 1) & btm) ? write_bit(1, reg) : write_bit(0, reg);
  }
  return true;
}

char *print_shift_register(ShiftRegister *reg)
{
  char *btm;
  btm = (char *)malloc(sizeof(bit) * 8);

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
  printf("Shift Register %s\n", btm);

  return btm;
}

void test_shift_register_config(void **state)
{
  ShiftRegister reg = {14, 11, 12};
  assert_int_equal(reg.SERIAL_PIN, 14);
  assert_int_equal(reg.SHIFT_REGISTER_CLOCK_PIN, 11);
  assert_int_equal(reg.LATCH_REGISTER_CLOCK_PIN, 12);
}

void test_write_bit(void **state)
{
  ShiftRegister reg = {14, 11, 12};
  write_bit(0, &reg);
  assert_int_equal(reg.serial_pin_state, 0);
  write_bit(1, &reg);
  assert_int_equal(reg.serial_pin_state, 1);
}

void test_write_bitmask(void **state)
{
  ShiftRegister reg = {14, 11, 12};
  write_bitmask(0b00010000, &reg);
  assert_int_equal(reg.serial_pin_state, 0);
  print_shift_register(&reg);
}

int main(int argc, char *argv[])
{
  printf("Runing Tests\n");

  void *state;

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_shift_register_config),
      cmocka_unit_test(test_write_bit),
      cmocka_unit_test(test_write_bitmask),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
