/*
 * C translation of the Fan_Speed_Control_Report.asm listing.
 * Target: PIC16F628A, built with a compatible MPLAB XC8 C compiler.
 * This is C, not C++.
 */
#include <xc.h>

/* The report specifies configuration word 0x3F10. Verify it for the board. */
__CONFIG(0x3F10);

static void set_duty(unsigned char value)
{
    CCPR1L = value;
}

void main(void)
{
    CMCON = 0x07;          /* Disable comparators; PORTA digital. */
    TRISA = 0x00;           /* RA0-RA3 are LED outputs. */
    TRISB = 0b00010111;     /* RB0,1,2,4 inputs; RB3/CCP1 output. */

    PR2 = 255;
    CCPR1L = 0;
    CCP1CON = 0b00001100;   /* CCP1 PWM mode. */
    T2CON = 0b00000100;     /* Timer2 on, prescaler 1:1. */
    PORTA = 0b00001111;     /* Keep all four indicator LEDs on. */

    for (;;) {
        /* Active-low switch checks; later active switches take priority. */
        if ((PORTB & 0b00000001) == 0) set_duty(0);
        if ((PORTB & 0b00000010) == 0) set_duty(85);
        if ((PORTB & 0b00000100) == 0) set_duty(170);
        if ((PORTB & 0b00010000) == 0) set_duty(255);
    }
}
