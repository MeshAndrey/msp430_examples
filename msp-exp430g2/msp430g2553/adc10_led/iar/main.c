#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;          // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON; // ADC10ON
  ADC10CTL1 = INCH_5;               // input A5
  ADC10AE0 |= BIT5;                         // PA.5 ADC option select
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start

    while (ADC10CTL1 & ADC10BUSY) {
      // no operation - just wait
      // only to use in education purposes
      // otherwise - use ISR
    };
    
    if (ADC10MEM < 512)
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
    else
      P1OUT |= 0x01;                        // Set P1.0 LED on
  }
}

