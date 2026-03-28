#include <msp430.h>

int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;

  // OUTPUT LEDS
  // Set P1.0 AND P1.6 to output direction
  P1DIR |= (BIT0 | BIT6);

  TACCR0 = 50000;
  TACCR1 = 25000;
  
  // CCR0 interrupt enabled
  TACCTL0 |= CCIE;
  TACCTL1 |= CAP | CCIE; // interrupt enabled
  // initial value
  TACCR0 = 50000;
  TACCR1 = 25000;
  
  TACTL |= TASSEL_2 /* Timer A clock source select: 2 - SMCLK */
           | ID_3   /* Timer A input divider: 3 - /8 */
           | MC_1   /* Timer A mode control: 1 - Up to CCR0 */
           | TACLR;  /* Timer A counter clear */

  // enable interrupts
  __bis_SR_register(GIE);

  while(1)
  {

  }
}

// Timer Interrupt Vector (TAIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA1_VECTOR
__interrupt void TIMER_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA1_VECTOR))) TIMER_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(TAIV)
  {
    case 0:
      break;                  
    case 0x20: // TACCR1
      TACCR1 += 25000;
      P1OUT ^= (BIT6);
      break;
    case 0xA0: // TAIFG / TACCR0
      P1OUT ^= (BIT0);
      break;
    default: break;
 }
}
