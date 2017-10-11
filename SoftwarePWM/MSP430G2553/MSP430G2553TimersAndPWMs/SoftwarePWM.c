#include <msp430.h>

int SoftwarePWM(void)
{
        WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

        //Port 1 declarations
        P1OUT &= 0x00;                      // P1OUT is set to 0
        P1DIR &= 0x00;                      // Port 1 direction is set to 0
        P1DIR |= 0x41;                      // Set P1.0 to output direction
        P1REN |= 0x08;                      // Resistor is connected to button
        P1OUT |= 0x08;                      // resistor is set to pull up

        //Timer A declarations
        TA0CCTL0  = CCIE;                   // CCR0 interrupt enabled
        TA0CCTL1  = CCIE;                   // CCR1 interrupt enabled
        TA0CCR0 = 1000;                     // TA0CCR0 is set
        TA0CCR1 = 500;                      // TA0CCR1 is set

        //Button interrupt
        P1IE   = 0x08;                      // P1.3 interrupt enabled, interrupt is enabled here, as well as interrupt clear
        P1IES |= 0x08;                      // interrupt edge select is defined
        P1IFG &= ~BIT3;                     // P1.3 IFG cleared


        TA0CTL  = TASSEL_2 + MC_1;
      __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0 w/ interrupt
}

/**
#pragma vector=PORT1_VECTOR                 //This is what happens when you enter the interrupt
__interrupt void Port_1(void)
{
    unsigned int i;

          if (TA0CCR1 == 1000){             //
            TA0CCR1 = 0;                    //
          }
          else{
            TA0CCR1 = TA0CCR1 + 100;        // increase brightness by 10%
          }
       for(i=0;i<5000;i++);                 // Delay
       P1IFG &= ~BIT3;                      // P1.3 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT |= 0x01;                          //
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
    switch(TA0IV){
    case 2:
    {
        P1OUT &= ~0x01;                     //
    } break;
    }
}
*/
