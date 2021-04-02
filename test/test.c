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
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

typedef bool bit;

typedef struct
{
  int SERIAL_PIN;
  int SHIFT_REGISTER_CLOCK_PIN;
  int LATCH_REGISTER_CLOCK_PIN;

  bool serial_pin_state;
} ShiftRegister;

bool write_bit(bit b, ShiftRegister *reg)
{
  reg->serial_pin_state = b;
  return b;
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

int main(int argc, char *argv[])
{
  printf("Runing Tests\n");

  void *state;

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_shift_register_config),
      cmocka_unit_test(test_write_bit),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
