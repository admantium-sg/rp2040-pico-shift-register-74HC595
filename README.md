# rp2040 Shift Register 74HC595 Library

C Library for working with the 74HC595 shift register.

## Example

How to switch on 8 LEDs:

```c
#include <rp2040_shift_register.h>

void main()
{
  ShiftRegister reg = shift_register_new((PinConfig){
      .SERIAL_PIN = 9,
      .SHIFT_REGISTER_CLOCK_PIN = 11,
      .STORAGE_REGISTER_CLOCK_PIN = 10});

  int switch_on = 0;

  while (true)
  {
    shift_register_write_bit(1, &reg);
    shift_register_flush(&reg);

    sleep_ms(1050);
    switch_on++;

    if (switch_on = 8)
    {
      shift_register_reset_storage(&reg);
      sleep_ms(1050);
      switch_on = 0;
    }
  }
}
```

## Objects

### PinConfig

Define the three pins necessary for connecting Pico with the shift register chip.

- `PinConfig.SERIAL_PIN`
- `PinConfig.SHIFT_REGISTER_CLOCK_PIN`
- `PinConfig.STORAGE_REGISTER_CLOCK_PIN`

### ShiftRegister

Object representing the shift register chip.

It has the following properties:

- `ShiftRegister.SERIAL_PIN`
- `ShiftRegister.SHIFT_REGISTER_CLOCK_PIN`
- `ShiftRegister.LATCH_REGISTER_CLOCK_PIN`
- `ShiftRegister.serial_pin_state`: The state of the SERIAL_PIN, which is `1` of `0`
- `ShiftRegister.register_state:` The `int8` value representing the current register

This object also defines its functions like `write_bit`, which you can call directly as `&reg->write_bit(&reg, 1)`. However, it is encouraged to use the public functions defined below.

## API Functions

- `ShiftRegister shift_register_new(PinConfig)`: Create a new shift register object
- `bool shift_register_write_bit(ShiftRegister *, bit)`: Write a single bit to the shift register, and perform a shift-right of all other bits. To output the shift registers' content, use `shift_register_flush`
- `bool shift_register_write_bitmask(ShiftRegister *, bitmask)`: Write a complete bitmask, e.g. `0b10101010` to the register. To output the shift registers' content, use `shift_register_flush`
- `bool shift_register_flush(ShiftRegister *)`: Flush the content of the shift register to the storage register.
- `bool shift_register_reset(ShiftRegister *)`: Resets the shift register's content to bitmask `0b00000000`.
- `bool shift_register_reset_storage(ShiftRegister *)` Resets the storage register's content to bitmask `0b00000000` and perforsm a `shift_register_flush()`
- `char * shift_register_print(ShiftRegister \*)` Prints the shift register's state as a bitmask, and returns a `char*` of the bitmask string.

## Testing

From the main directory, compile and run the tests.

```bash
clang -std=c17 -L /usr/local/Cellar/cmocka/1.1.5/lib/ -lcmocka -I src -I test -DLIBTEST -o test.bin test/test.c src/rp2040_shift_register.c && ./test.bin
```

## License

[BSD-3-Clause](LICENSE)
