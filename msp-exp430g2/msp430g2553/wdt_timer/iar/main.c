#include <msp430.h>

int main(void)
{
  // Set Watchdog Timer interval
  WDTCTL = WDT_MDLY_32;
  // Enable WDT interrupt
  IE1 |= WDTIE;
  // Set P1.0 and P1.6 to output direction
  P1DIR |= BIT0 | BIT6;

  __bis_SR_register(GIE);
  
  while (1) {
    ;
  }
}

// Watchdog Timer ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
  // Toggle P1.0 and P1.6 using XOR
  P1OUT ^= BIT0 | BIT6;
}