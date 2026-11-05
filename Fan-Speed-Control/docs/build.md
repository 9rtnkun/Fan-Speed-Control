# Build instructions and limitations

## C translation

Install MPLAB X and MPLAB XC8 with a device family pack that lists PIC16F628A. XC8 targets this 8-bit PIC family using **C**; it is not a C++ compiler. Build `src/fan_control.c` as a PIC16F628A project in MPLAB X, select the appropriate oscillator and configuration bits for the actual board, and inspect the generated map/listing before programming. The exact command-line options can vary with the XC8 release and installed pack; the MPLAB X project generator supplies the matching device and pack settings.

Example command form for an installed XC8 version (verify paths and accepted options for that release):

```sh
xc8-cc -mcpu=16F628A -o build/fan_control.elf src/fan_control.c
```

The compiler normally emits an Intel HEX as a build artifact. This repository intentionally contains no `.hex`: the available compiler installation was incomplete and no successful compatible build was performed.

## Original Assembly

The listing uses MPASM directives (`LIST`, `__CONFIG`, `BANKSEL`, `ORG`) and includes `P16F628A.INC`. To recreate the report's assembly build, install a compatible MPASM/MPLINK release and device include files, assemble for `16F628A`, then link the resulting object to produce HEX. MPASM/MPLINK are legacy tools; confirm availability and device support in the selected MPLAB X release before following that route.

## Validation before use

- The listing sets configuration word `0x3F10`; confirm that oscillator, watchdog, code protection, and other bits suit the hardware.
- PIC16F628A has no internal pull-up on PORTB. Provide suitable external pull-ups for active-low switches or verify the simulator's switch model.
- Use a transistor/MOSFET or suitable fan driver stage, common ground, and flyback protection as appropriate. Never power a fan from RB3.
- The report's stated duty percentages conflict with its `PR2=255` and `CCPR1L=85/170/255` values; determine desired output timing before claiming the percentages.
- The code does not debounce switches and polls continuously.
