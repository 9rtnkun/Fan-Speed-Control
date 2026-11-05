# Pin assignment and behavior

| PIC16F628A pin | Function | Connection |
|---|---|---|
| RA0–RA3 | Digital outputs, driven high | Four indicator/backlight LEDs (use appropriate current limiting) |
| RB0 | Active-low digital input | SW0, stop / 0% request |
| RB1 | Active-low digital input | SW1, low / approximately 33% request |
| RB2 | Active-low digital input | SW2, medium / approximately 66% request |
| RB3 / CCP1 | PWM output | Fan driver input; do not drive a motor directly from the PIC pin |
| RB4 | Active-low digital input | SW3, high / maximum request |

The report specifies `TRISB = 00010111b`, `PR2 = 255`, Timer2 prescaler 1:1, CCP1 PWM mode, and duty register values 0, 85, 170, and 255. Switches are sampled continuously. The checks run SW0, SW1, SW2, SW3 in sequence, so SW3 has priority when multiple switches are low.

The report describes those duty values as 0%, ~33%, ~66%, and 100%. On the PIC PWM's 10-bit duty scale with PR2=255, 255 is approximately 25% of the full-scale count (not 100%). Verify the intended PWM scaling against the actual PIC datasheet and simulation: the report's stated percentages do not match the register values as written. A true near-100% request needs the high duty bits configured too, or a different output strategy.
