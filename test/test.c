/* 
* ---------------------------------------
* Copyright (c) Sebastian Günther 2021  |
*                                       |    
* devcon@admantium.com                  |    
*                                       | 
* SPDX-License-Identifier: BSD-3-Clause | 
* ---------------------------------------
*/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdio.h>
#include <admantium/rp2040_shift_register.h>

ShiftRegister reg;

void test_shift_register_config(void **state)
{
  reg = shift_register_new((PinConfig){
      .SERIAL_PIN = 14,
      .SHIFT_REGISTER_CLOCK_PIN = 11,
      .STORAGE_REGISTER_CLOCK_PIN = 12});

  assert_int_equal(reg.SERIAL_PIN, 14);
  assert_int_equal(reg.SHIFT_REGISTER_CLOCK_PIN, 11);
  assert_int_equal(reg.STORAGE_REGISTER_CLOCK_PIN, 12);
}

void test_write_bit(void **state)
{
  shift_register_write_bit(&reg, 1);
  assert_int_equal(reg.serial_pin_state, 1);
  shift_register_write_bit(&reg, 0);
  assert_int_equal(reg.serial_pin_state, 0);

  printf("[0b%s]\n", shift_register_print(&reg));
  assert_memory_equal(shift_register_print(&reg), &"01000000", 8);
}

void test_write_bitmask(void **state)
{
  shift_register_write_bitmask(&reg, 0b00010000);
  assert_int_equal(reg.serial_pin_state, 0);

  printf("[0b%s]\n", shift_register_print(&reg));
  assert_memory_equal(shift_register_print(&reg), &"00010000", 8);
}

void test_reset_shift_register(void **state)
{
  shift_register_write_bitmask(&reg, 0b01110001);
  shift_register_reset(&reg);

  assert_memory_equal(shift_register_print(&reg), &"00000000", 8);
  printf("[0b%s]\n", shift_register_print(&reg));
}

int main(int argc, char *argv[])
{
  printf("Runing Tests\n");

  void *state;

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_shift_register_config),
      cmocka_unit_test(test_write_bit),
      cmocka_unit_test(test_write_bitmask),
      cmocka_unit_test(test_reset_shift_register),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
