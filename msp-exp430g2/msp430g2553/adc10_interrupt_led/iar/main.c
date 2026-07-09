#include <msp430.h>
#include <stdint.h>

uint8_t interruptHandled = 0;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_5;                       // input A1
  ADC10AE0 |= BIT5;                         // PA.1 ADC option select
  P1DIR |= BIT0;                            // Set P1.0 to output direction

   __bis_SR_register(GIE);
  for (;;){
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    
    while (!interruptHandled) {};
    
    if (ADC10MEM < 512)
      P1OUT &= ~BIT0;                       // Clear P1.0 LED off
    else
      P1OUT |= BIT0;                        // Set P1.0 LED on
    
    interruptHandled = 0;
  }
}

// ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  interruptHandled  = 1;
}
