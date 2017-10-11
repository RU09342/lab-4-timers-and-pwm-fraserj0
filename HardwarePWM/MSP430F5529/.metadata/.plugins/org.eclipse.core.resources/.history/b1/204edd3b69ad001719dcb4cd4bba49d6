/**
#include <msp430.h>


int Debouncing()
{
    WDTCTL = WDTPW + WDTHOLD;

   //******GPIO Setup*******

    P1DIR &= 0x00;
    P1DIR |= BIT0;
    P1OUT &= 0x00;
    P1OUT |= BIT1;
    P1REN |= BIT1;
    TA0CCTL0  = CCIE;
    TA0CCR0 = 32000;
    P1IFG &= ~BIT1;
    P1IE   = BIT1;
    P1IES |= BIT1;

    _bis_SR_register(LPM0_bits + GIE);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT  ^= BIT0;
    TA0CTL  = TASSEL_2 + MC_1 ;
    P1IE  &= ~BIT1;
    P1IFG &= ~BIT1;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1IE |= BIT1;
    TA0CTL = MC_0;
    TA0CTL = TACLR;
}
*/



