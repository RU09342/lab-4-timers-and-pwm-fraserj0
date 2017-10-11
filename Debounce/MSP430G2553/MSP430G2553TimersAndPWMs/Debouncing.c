/**

#include <msp430.h>


int Debouncing()
{
    WDTCTL = WDTPW + WDTHOLD;

   //******GPIO Setup*******

    //Port 1 is initialized
    P1DIR &= 0x00;                          // Port 1 direction is set
    P1DIR |= BIT0;                          // Port 1 direction is set
    P1OUT &= 0x00;                          // Port 1 outputs nothing
    P1OUT |= BIT3;                          // resistor is pulled up
    P1REN |= BIT3;                          // resistor is placed on button

    //Timer 0 is initialized
    TA0CCTL0  = CCIE;                       // timer0 is enabled
    TA0CCR0 = 32000;                        // TA0CCR0 is set

    //Button interrupt is enabled
    P1IFG &= ~BIT3;                         // flag is cleared
    P1IE   = BIT3;                          // interrupt enabled
    P1IES |= BIT3;                          // interrupt edge is selected

    _bis_SR_register(LPM0_bits + GIE);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT  ^= BIT0;                         // LED1 is toggled
    TACTL  = TASSEL_2 + MC_1 ;              // Timer A starts, smclock, up mode
    P1IE  &= ~BIT3;                         // interrupt disabled
    P1IFG &= ~BIT3;                         // interrupt flag is cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1IE |= BIT3;                           // button interrupt is re-enabled
    TA0CTL = MC_0;                          // timer 0 is set to down
    TA0CTL = TACLR;                         // timer is cleared
}
*/
