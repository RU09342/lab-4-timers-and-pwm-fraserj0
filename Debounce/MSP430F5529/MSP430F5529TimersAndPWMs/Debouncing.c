/**
#include <msp430.h>


int Debouncing()
{
    WDTCTL = WDTPW + WDTHOLD;

   //******GPIO Setup*******

    //P1 declarations
    P1DIR &= 0x00;                         // P1 direction is set
    P1DIR |= BIT0;                         // P1 direction is set
    P1OUT &= 0x00;                         // P1 out is set
    P1OUT |= BIT1;                         // LED is set as an output
    P1REN |= BIT1;                         // resistor is set on button

    //Timer declarations
    TA0CCTL0  = CCIE;                      // Timer0 is enabled
    TA0CCR0 = 32000;                       // CCR0 is set

    //button interrupt
    P1IFG &= ~BIT1;                        // Interrupt flag is set
    P1IE   = BIT1;                         // interrupt enable is set
    P1IES |= BIT1;                         // edge select is set high

    _bis_SR_register(LPM0_bits + GIE);
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT  ^= BIT0;                         // toggle led1
    TA0CTL  = TASSEL_2 + MC_1 ;             // timer starts, up mode, sm clock
    P1IE  &= ~BIT1;                         // disables interrupt
    P1IFG &= ~BIT1;                         // clears interrupt flag
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1IE |= BIT1;                           // enables interrupt
    TA0CTL = MC_0;
    TA0CTL = TACLR;                         //timer is cleared
}
*/



