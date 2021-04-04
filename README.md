# rp2040 Shift Register 74HC595 Library

C Library for working with the 74HC595 shift register.

## API

```C
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
```

## Testing

From the main directory, compile and run the tests.

```bash
clear && clang -std=c17 -L /usr/local/Cellar/cmocka/1.1.5/lib/ -lcmocka -I src test/test.c src/rp2040_shift_register.c -o c.bin && ./c.bin
```

License: BSD-3-Clause
