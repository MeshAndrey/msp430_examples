#include <msp430.h>

/*
  This example shows how to use GPIO in output mode.
  Each loop iteration GPIO states are inverted.
  This results to LED blinking on connected Pins 1.0 and 1.1

                MSP430F5438A
             -----------------
         /|\|                 |
          | |                 |
          --|RST              |
            |                 |
            |             P1.0|--> LED1
            |             P1.1|--> LED2

*/


int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  // Set P1.0 AND P1.1 to output direction
  P1DIR |= (BIT0 | BIT1);
  
  while(1)
  {
    // Invert gpio state
    P1OUT ^= (BIT0 | BIT1);
    // simple time delay
    __delay_cycles(1000000);
  }
}