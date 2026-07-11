#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;

  P1OUT |= BIT0 | BIT1;
  P1DIR |= BIT0 | BIT1;

  // Setup RTC Timer
  RTCCTL01 = RTCTEVIE + RTCSSEL_2 + RTCTEV_0;
  RTCPS0CTL = RT0PSDIV_2;
  RTCPS1CTL = RT1SSEL_2 + RT1PSDIV_3;

  __bis_SR_register(GIE);
  
  while (1) {
    ;
  }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(RTC_VECTOR))) RTC_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(RTCIV,16))
  {
    case 4: // RTCEVIFG
      P1OUT ^= BIT0 | BIT1;
      break;

    default: 
      break;
  }
}
