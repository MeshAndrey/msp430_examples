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
  
  // PxIFG flag is set with a high-to-low transition
  P1IES |= (BIT3);
  // P1IE
  P1IE |= (BIT3);
  // An interrupt bit is cleared
  P1IFG &= ~(BIT3);
  // Enable interrupts
  __bis_SR_register(GIE); 
  
  while(1)
  {

  }
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
  // Toggle LEDS
  P1OUT ^= (BIT0 | BIT6); 
  // P1.3 IFG cleared
  P1IFG &= ~(BIT3);
}
