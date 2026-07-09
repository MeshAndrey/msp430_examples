#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent timeout reset
    
    // Measured - 50 Hz 
    P1DIR |= BIT0;            // Set P1.0 (ACLK) as an output
    P1SEL |= BIT0;            // Select the ACLK peripheral function for P1.0
    
    // Measured - ~1,043 MHz
    // But should be 1.1 MHz...
    P1DIR |= BIT4;            // Set P1.4 (SMCLK) as an output
    P1SEL |= BIT4;            // Select the SMCLK peripheral function for P1.4

    while(1) {
        // Low power modes or other background tasks
    }
}