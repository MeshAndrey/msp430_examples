#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent timeout reset
    
    // 0 - ACLK, 1 - MCLK, 2 - SMCLK
    // 32.877 kHz, 1.043 MHz, 1.043 MHz by default
    P11DIR |= BIT0 | BIT1 | BIT2;
    P11SEL |= BIT0 | BIT1 | BIT2;
    
    while(1) {
        // Low power modes or other background tasks
    }
}
