# Raspberry Pico Shift Register 74HC595 Library

C Library for working with the 74HC595 shift register.

## Table of Content

- [Example](#example)
- [Documentation](#documentation)
  - [PinConfig Object](#pinconfig-object)
  - [ShiftRegister Object](#shiftregister-object)
  - [API Functions](#api-functions)
- [Building the Examples](#building-the-examples)
- [Building the Tests](#building-the-tests)
- [License](#license)

## Example

Write individual bits and a complete bitmask:

```c
#include <admantium/pico/shift_register_74HC595.h>

void main()
{
  ShiftRegister reg = shift_register_new((PinConfig){
    .SERIAL_PIN = 9,
    .SHIFT_REGISTER_CLOCK_PIN = 11,
    .STORAGE_REGISTER_CLOCK_PIN = 10
  });

  shift_register_write_bit(&reg, 1);
  shift_register_flush(&reg);

  shift_register_write_bitmask(&reg, 0b10101010);
  shift_register_flush(&reg);

  shift_register_reset_storage(&reg);
}
```

How to switch on 8 LEDs:

```c
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

    if (switch_on == 8)
    {
      shift_register_reset_storage(&reg);
      sleep_ms(1050);
      switch_on = 0;
    }
  }
}
```

## Documentation

### PinConfig Object

Define the three pins necessary for connecting Pico with the shift register chip.

* `PinConfig.SERIAL_PIN`
* `PinConfig.SHIFT_REGISTER_CLOCK_PIN`
* `PinConfig.STORAGE_REGISTER_CLOCK_PIN`

### ShiftRegister Object

Object representing the shift register chip.

It has the following properties:

* `ShiftRegister.SERIAL_PIN`
* `ShiftRegister.SHIFT_REGISTER_CLOCK_PIN`
* `ShiftRegister.LATCH_REGISTER_CLOCK_PIN`
* `ShiftRegister.serial_pin_state`: The state of the SERIAL_PIN, which is `1` of `0`
* `ShiftRegister.register_state:` The `int8` value representing the current register

This object also defines its functions like `write_bit`, which you can call directly as `&reg->write_bit(&reg, 1)`. However, it is encouraged to use the public functions defined below.

### API Functions

* `ShiftRegister shift_register_new(PinConfig)`: Create a new shift register object
* `bool shift_register_write_bit(ShiftRegister *, bool)`: Write a single bit to the shift register, and perform a shift-right of all other bits. To output the shift registers' content, use `shift_register_flush`
* `bool shift_register_write_bitmask(ShiftRegister *, u_int8_t)`: Write a complete bitmask, e.g. `0b10101010` to the register. To output the shift registers' content, use `shift_register_flush`
* `bool shift_register_flush(ShiftRegister *)`: Flush the content of the shift register to the storage register.
* `bool shift_register_reset(ShiftRegister *)`: Resets the shift register's content to bitmask `0b00000000`.
* `bool shift_register_reset_storage(ShiftRegister *)` Resets the storage register's content to bitmask `0b00000000` and performs a `shift_register_flush()`
* `char * shift_register_print(ShiftRegister \*)` Prints the shift register's state as a bitmask, and returns a `char*` of the bitmask string.

## Building the Examples

You need to configure the environment variable `PICO_SDK_PATH`.

From the main directory:

```sh
rm -rvf build
cmake -B build -S . -DEXAMPLE_BUILD=ON
make -C build/example
```

Files are contained in `build/examples.

```sh
8_led_blink.bin
8_led_blink.dis
8_led_blink.elf
8_led_blink.elf.map
8_led_blink.hex
8_led_blink.uf2
```

## Building the Tests

You need to configure the environment variable `PICO_SDK_PATH`.

From the main directory, compile and run the tests.

```sh
rm -rvf build
cmake -B build -S . -DTEST_BUILD
make -C build/src && make -C build/test
```

Run tests with `build/test/pico_shift_register.tests.bin`

```c
Runing Tests
[==========] Running 4 test(s).
[ RUN      ] test_shift_register_config
[       OK ] test_shift_register_config
[ RUN      ] test_write_bit
[0b01000000]
[       OK ] test_write_bit
[ RUN      ] test_write_bitmask
[0b00010000]
[       OK ] test_write_bitmask
[ RUN      ] test_reset_shift_register
[0b00000000]
[       OK ] test_reset_shift_register
[==========] 4 test(s) run.
[  PASSED  ] 4 test(s).
```

## License

[BSD-3-Clause](LICENSE)
