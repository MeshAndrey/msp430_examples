#include <msp430.h>

int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;

  // OUTPUT LEDS
  // Set P1.0 AND P1.6 to output direction
  P1DIR |= (BIT0 | BIT6);

  TACTL |= TASSEL_2 /* Timer A clock source select: 2 - SMCLK */
           | ID_3   /* Timer A input divider: 3 - /8 */
           | MC_2   /* Timer A mode control: 2 - Continous up */
           | TACLR  /* Timer A counter clear */
           | TAIE;  /* Timer A counter interrupt enable */

  // enable interrupts
  __bis_SR_register(GIE);

  while(1)
  {

  }
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA1_VECTOR
__interrupt void TIMER_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA1_VECTOR))) TIMER_ISR (void)
#else
#error Compiler not supported!
#endif
{
  // Toggle LEDs
  P1OUT ^= (BIT0 | BIT6);
  // Not reading from TAIV register. So manually clearing the bit
  TACTL &= ~TAIFG;
}
