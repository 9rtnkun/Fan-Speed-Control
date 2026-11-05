# PIC16F628A Fan Speed Control

This project documents the four-level fan PWM controller described in `Fan_Speed_Control_Report.docx`.

## Project files

- `src/fan_control.c` is an XC8 C translation of the report's control flow. It is C, not C++; XC8 does not compile C++ for this 8-bit PIC target.
- `original/Fan.asm` is a transcription of the Assembly listing embedded in the report. The report's Thai legacy-encoded text did not extract cleanly, so comments have been normalized to English and this file cannot be certified as a character-for-character copy. Instructions and control flow are retained.
- `docs/pin-assignment.md` lists the wiring and behavior.
- `docs/build.md` contains a reproducible build recipe and explains why this package has no HEX file.

## Controller behavior

Four active-low switches select duty requests 0, 85, 170, or 255 through CCP1 on RB3. The original polling order means that if more than one switch is held, the last active switch in the order SW0, SW1, SW2, SW3 wins. RA0–RA3 are continuously high for indicator/backlight LEDs.

## Toolchain and firmware status

PIC16F628A is an 8-bit PIC target for Microchip's XC8 C toolchain, but the supported language is C, not C++. The installed `C:\Program Files\Microchip\xc8\v3.10` directory on the authoring machine contains only an `etc` folder; no compiler executable or usable build toolchain was present. No HEX was generated or included. See `docs/build.md` for steps to build with a complete XC8 installation and its device support pack, or to assemble the original source with the legacy MPASM/MPLINK tools.

The C translation is a source port and has not been compiled or tested on hardware. Check configuration bits, oscillator assumptions, the selected device pack, and fan driver circuitry before programming a device.

## Example

![turn off](0.jpg)
![speed 1](Fan-Speed-Control/blob/main/1.jpg)
![speed 2](Fan-Speed-Control/blob/main/2.jpg)
![speed 3](Fan-Speed-Control/blob/main/3.jpg)
