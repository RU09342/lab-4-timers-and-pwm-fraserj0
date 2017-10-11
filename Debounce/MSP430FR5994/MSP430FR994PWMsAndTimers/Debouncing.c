/**#include<msp430fr5994.h>
void Debouncing(void){

            P1OUT &= 0x00;                    //Shut everything down
            P1DIR &= 0x00;
            P1DIR |= 0x03;                    // Set P1.0 and P1.6 to output direction
            P5OUT &= 0x00;                    //Shut Port 5 Down
            P5DIR &= 0x00;
            P5OUT |= BIT6;                    //Select pull-up mode for P5.6
            P5REN |= BIT6;                    // Enable internal pull-up/down resistors
            P5IE |= BIT6;                     // P5.6 interrupt enabled
            P5IES |= BIT6;                    // P5.6 Hi/lo edge
            P5IFG &= ~BIT6;                   // P5.6 IFG cleared


        //Timer B
        TA0CCTL0 = CCIE;                      // TA0CCR0 interrupt enabled


        __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0 w/ interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
  if(P5IES & BIT6){
   TA0CCR0 = 3000;
   TA0CTL = TBSSEL_2 + MC_1+ID_3;             //Start TimerA_0
   P1OUT ^= BIT0;                             //Toggle LEDs
   P1OUT ^= BIT1;
   P5IES &= ~BIT6;                            //Flip edge
   P5IE &= ~BIT6;                             //Disable interrupt
  }
  else{
         TA0CCR0 =3000;
         TA0CTL = TBSSEL_2 + MC_1+ID_3;       //Start TimerA_0
         P5IES |= BIT6;
         P5IE &= ~BIT6;                       //Disable interrupt
  }

  P5IFG &= ~BIT6;                             // P5.6 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{

   P5IE |=BIT6;
   TA1CTL = MC_0;                           //Halt TimerA_1
   TA1CTL = TACLR;                          //Turn off TimerA_1


}*/

