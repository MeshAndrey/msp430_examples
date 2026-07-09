#include <msp430.h>
#include <stdint.h>

static volatile uint8_t interruptHandled;


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;          // Stop watchdog
  ADC10CTL1 = ADC10DIV_3 + INCH_10;  // A10
  ADC10CTL0 = SREF_1 + REFON + ADC10ON + ADC10SHT_3 + ADC10IE;

  __bis_SR_register(GIE);
  for (;;){
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    
    while (!interruptHandled) {};
    
    const uint16_t adcTempValue = ADC10MEM;
    // 2 ^ 10 = 1024 - ADC Resolution
    // 3.3V = 1024   - Max ADC Value
    // X V = ADC_VALUE - Voltage Level that we are searching for 
    // X V = (ADC_VALUE * 3.3V) / 1024;
    
    // WARNING: Do not use this code in real project
    // MSP430 does not have FPU, so this math operation will be executed on CPU very slow
    
    // Does not use any calibration
    // Have bad precision
    const float adcVoltage = (((float)adcTempValue) * 1.5) / (float)1024;
    const float tempDegC = (adcVoltage -  0.986) /  0.00355;
    
    // AI-generated not working shit
    // const float tempDegC1 = ( ( adcTempValue - CAL_ADC_15T30) * 55) / ( CAL_ADC_15T85 - CAL_ADC_15T30) + 25;
    
    // Some indian guy's convertion without any explaination. And it somehow works
    // const uint16_t tempDegC2 = ((adcTempValue * 27069L - 18169625L) >> 16);
    
    // Set breakpoint on next line to see calculated values
    interruptHandled = 0;
  }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
  interruptHandled = 1;
}
