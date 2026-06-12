#include <msp430.h>
#include <stdint.h>

int main(void)
{
  // Stop WDT
  WDTCTL = WDTPW | WDTHOLD;
  /* Port 5 Selection */
  P5SEL |= BIT6 | BIT7 ;
  /* Port 5 Selection 2 */
  // P5SEL2 |= BIT6 | BIT7;
  // USCI A0 Control Register 1, USCI 0 Clock Source: 2  // 10b = SMCLK
  UCA1CTL1 |= UCSSEL_2;
  // 1MHz 9600
  // USCI_Ax Baud-Rate Control 0 Register
  UCA1BR0 = 104;
  // USCI_Ax Baud-Rate Control 1 Register
  UCA1BR1 = 0;
  // Modulation UCBRSx = 1
  // USCI A0 Modulation Control
  // USCI Second Stage Modulation Select 0
  UCA1MCTL = UCBRS0;
  // **Initialize USCI state machine**
  // USCI A0 Control Register 1, USCI Software Reset
  UCA1CTL1 &= ~UCSWRST;
  
  uint8_t counter = 0;
  
  while (1)
  {
    UCA1TXBUF = counter; // send counter byte. printable char begins from '0'/0x30
    counter++;
    
    __delay_cycles(1000000); // ~1 second delay
  }
}
