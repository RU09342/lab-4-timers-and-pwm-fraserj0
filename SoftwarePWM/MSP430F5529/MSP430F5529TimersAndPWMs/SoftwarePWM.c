#include <msp430.h>
/**
int SoftwarePWM(void)
{
        WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer

        //P1OUT declarations
        P1OUT &= 0x00;
        P1DIR &= 0x00;
        P1DIR |= 0x01;                              // Set P1.0 to output direction
        P1REN |= 0x02;
        P1OUT |= 0x02;

        //Timer declarations
        TA0CCTL0  = CCIE;                           // CCR0 interrupt enabled
        TA0CCTL1  = CCIE;

        //Button interrupt
        P1IE   = 0x02;                              // P1.3 interrupt enabled, interrupt is enabled here, as well as interrupt clear
        P1IES |= 0x02;
        P1IFG &= ~BIT1;                             // P1.3 IFG cleared


        TA0CCR0 = 1000;
        TA0CCR1 = 500;


        TA0CTL  = TASSEL_2 + MC_1;
      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}


#pragma vector=PORT1_VECTOR                 //This is what happens when you enter the interrupt
__interrupt void Port_1(void)
{
    unsigned int i;

          if (TA0CCR1 == 1000){
            TA0CCR1 = 0;
          }
          else{
            TA0CCR1 = TA0CCR1 + 100;
          }
       for(i=0;i<5000;i++);                 //Delay
       P1IFG &= ~BIT1;                      // P1.3 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT |= 0x01;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
    switch(TA0IV){
    case 2:
    {
        P1OUT &= ~0x01;
    } break;
    }
}
*/


