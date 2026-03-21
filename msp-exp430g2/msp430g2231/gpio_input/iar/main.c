#include <msp430.h>

int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  // OUTPUT LEDS
  // Set P1.0 AND P1.6 to output direction
  P1DIR |= (BIT0 | BIT6);
  
  // INPUT BUTTON
  // Set P1.3 to input direction
  P1DIR &= ~(BIT3);
  // Set P1.3 Resistor enable register (for input)
  P1REN |= (BIT3);
  // Set the pin is pull-up
  P1OUT |= (BIT3);
  
  while(1)
  {
    if (P1IN & BIT3) {
      P1OUT &= ~(BIT0 | BIT6);
    } else {
      P1OUT |= (BIT0 | BIT6);
    }
  }
}