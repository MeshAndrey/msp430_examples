#include <msp430.h>
#include <stdint.h>

// NOT A PRODUCTION READY CODE

#define LEFT_BIT   BIT1
#define RIGHT_BIT  BIT2
#define SELECT_BIT BIT3
#define UP_BIT     BIT4
#define DOWN_BIT   BIT5
#define SW1_BIT    BIT6
#define SW2_BIT    BIT7

#define BUTTONS_MASK (LEFT_BIT | RIGHT_BIT | SELECT_BIT | \
                      UP_BIT   | DOWN_BIT  | SW1_BIT    | SW2_BIT)

uint8_t byteToSend = '\0';

int main(void)
{
  // Stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;
  
  // OUTPUT LEDS
  // Set P1.0 AND P1.1 to output direction
  P1DIR |= (BIT0 | BIT1);
  
  // INPUT BUTTON
  // Set P2.6 to input direction
  P2DIR &= ~(BUTTONS_MASK);
  // Set P2.6 Resistor enable register (for input)
  P2REN |= (BUTTONS_MASK);
  // Set the pin is pull-up
  P2OUT |= (BUTTONS_MASK);
  
  // PxIFG flag is set with a high-to-low transition
  P2IES |= (BUTTONS_MASK);
  // P1IE
  P2IE |= (BUTTONS_MASK);
  // An interrupt bit is cleared
  P2IFG &= ~(BUTTONS_MASK);
  // Enable interrupts
  __bis_SR_register(GIE);
  
  // UART configuration
  /* Port 5 Selection */
  P5SEL |= BIT6 | BIT7 ;
  /* Port 5 Selection 2 */
  // P5SEL2 |= BIT6 | BIT7;
  // USCI A0 Control Register 1, USCI 0 Clock Source: 2  // 10b = SMCLK
  UCA1CTL1 |= UCSSEL_2;
  // ~ 1_126_400 Hz 9600
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

  while(1) {
    if (byteToSend == '\0') {
      continue;
    }

    UCA1TXBUF = byteToSend;
    byteToSend = '\0';
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
  
  switch (P2IFG) {
  case LEFT_BIT:
    byteToSend = 'L';
    break;
   case RIGHT_BIT:
    byteToSend = 'R';
    break;
   case SELECT_BIT:
    byteToSend = 'S';
    break;
   case UP_BIT:
    byteToSend = 'U';
    break;
   case DOWN_BIT:
    byteToSend = 'D';
    break;
   case SW1_BIT:
    byteToSend = '1';
    break;
   case SW2_BIT:
    byteToSend = '2';
    break;
  default:
    break;
  }
  /* Clear all interrupt bits */
  P2IFG = 0;
  
}
