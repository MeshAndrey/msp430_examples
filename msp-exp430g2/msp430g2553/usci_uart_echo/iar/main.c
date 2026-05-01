#include <msp430.h>
#include <stdint.h>

int main(void)
{
  // Stop WDT
  WDTCTL = WDTPW | WDTHOLD;
  /* Port 1 Selection */
  P1SEL |= BIT1 | BIT2 ;
  /* Port 1 Selection 2 */
  P1SEL2 |= BIT1 | BIT2;
  // USCI A0 Control Register 1, USCI 0 Clock Source: 2  // 10b = SMCLK
  UCA0CTL1 |= UCSSEL_2;
  // 1MHz 9600
  // USCI_Ax Baud-Rate Control 0 Register
  UCA0BR0 = 104;
  // USCI_Ax Baud-Rate Control 1 Register
  UCA0BR1 = 0;
  // Modulation UCBRSx = 1
  // USCI A0 Modulation Control
  // USCI Second Stage Modulation Select 0
  UCA0MCTL = UCBRS0;
  // **Initialize USCI state machine**
  // USCI A0 Control Register 1, USCI Software Reset
  UCA0CTL1 &= ~UCSWRST;
  
  // Enable USCI_A0 RX interrupt
  IE2 |= UCA0RXIE;

  __bis_SR_register(GIE);
  while (1)
  {
  }
}

// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
  // wait for register ready
  while (!(IFG2&UCA0TXIFG));
  // send back received byte
  UCA0TXBUF = UCA0RXBUF;
}

