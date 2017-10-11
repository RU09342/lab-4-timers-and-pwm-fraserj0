/**#include<msp430fr2311.h>
void Debouncing(void){

        P2OUT &= 0x00;      //Shut everything down
        P2DIR &= 0x00;
        P2DIR |= 0x01;
        P1OUT &= 0x00;      //Shut everything down
        P1DIR &= 0x00;
        P1DIR |= 0x01;      // Set P1.0 to output direction
        P1REN |= 0x02;
        P1OUT |= 0x02;
        P1IE  |= 0x02;      // P1.1 interrupt enabled
        P1IES |= 0x02;
        P1IFG &= ~BIT1;     // P1.1 IFG cleared

        //Timer B
        TB0CCTL0 = CCIE;                          // TB0CCR0 interrupt enabled


        __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  if(P1IES & BIT1){
   TB0CCR0 = 3000;
   TB0CTL = TBSSEL_2 + MC_1+ID_0;            //Start TimerB_0
   P1OUT ^= BIT0;                            //Toggle LEDs
   P2OUT ^= BIT0;
   P1IES &= ~BIT1;                           //Flip edge
   P1IE &= ~BIT1;                            //Disable interrupt
  }
  else{
         TB0CCR0 = 3000;
         TB0CTL = TBSSEL_2 + MC_1+ID_0;      //Start TimerB_0
         P1IES |= BIT1;
         P1IE &= ~BIT1;                      //Disable interrupt
  }

  P1IFG &= ~BIT1;                            // P1.1 IFG cleared
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{

   P1IE |=BIT1;
   TB1CTL = MC_0;                           //Halt TimerB_1
   TB1CTL = TBCLR;                          //Turn off TimerB_1


}*/









