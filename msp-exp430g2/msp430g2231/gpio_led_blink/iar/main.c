#include <msp430.h>

int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  // Set P1.0 AND P1.6 to output direction
  P1DIR |= (BIT0 | BIT6);
  
  while(1)
  {
    P1OUT ^= (BIT0 | BIT6);
    __delay_cycles(1000000);
  }
}