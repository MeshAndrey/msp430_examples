#include <msp430.h>

int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  // OUTPUT LEDS
  // Set P1.0 AND P1.1 to output direction
  P1DIR |= (BIT0 | BIT1);
  
  // INPUT BUTTON
  // Set P2.6 to input direction
  P2DIR &= ~(BIT6);
  // Set P2.6 Resistor enable register (for input)
  P2REN |= (BIT6);
  // Set the pin is pull-up
  P2OUT |= (BIT6);
  
  // PxIFG flag is set with a high-to-low transition
  P2IES |= (BIT6);
  // P1IE
  P2IE |= (BIT6);
  // An interrupt bit is cleared
  P2IFG &= ~(BIT6);
  // Enable interrupts
  __bis_SR_register(GIE); 
  
  while(1)
  {

  }
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
  // Toggle LEDS
  P1OUT ^= (BIT0 | BIT1); 
  // P2.6 IFG cleared
  P2IFG &= ~(BIT6);
}
