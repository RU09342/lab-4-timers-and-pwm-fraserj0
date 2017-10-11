#include<msp430fr5994.h>
void MultipleButtnDebounce(void){

            P1OUT &= 0x00;                        //Shut everything down
            P1DIR &= 0x00;
            P1DIR |= 0x03;                        // Set P1.0 and P1.6 to output direction
            P5OUT &= 0x00;                        //Shut Port 5 Down
            P5DIR &= 0x00;
            P5OUT |= BIT6 +BIT5;                  //Select pull-up mode for P5.6 and P5.5
            P5REN |= BIT6 +BIT5;                  // Enable internal pull-up/down resistors
            P5IE |= BIT6+BIT5;                    // P5.6 and P5.5 interrupt enabled
            P5IES |= BIT6+BIT5;                   // P5.6 and P5.5 Hi/lo edge
            P5IFG &= ~BIT6+(~BIT5);               // P5.6 and P5.5 IFG cleared


        //Timer B
        TA0CCTL0 = CCIE;                          // TA0CCR0 interrupt enabled
        TB0CCTL0 |= CCIE;                         //TB0CCR1 interrupt enabled

        __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
  if(P5IFG & BIT6){                               //Check if P5.6 interrupt
  if(P5IES & BIT6){
   TA0CCR0 = 5000;
   TA0CTL = TASSEL_2 + MC_1+ID_3;                 //Start TimerA_0
   P1OUT ^= BIT0;                                 //Toggle LEDs
   P5IES &= ~BIT6;                                //Flip edge
   P5IE &= ~BIT6;                                 //Disable interrupt
   P5IFG &= ~BIT6;                                // P5.6 IFG cleared
  }
  else{
         TA0CCR0 =5000;
         TA0CTL = TASSEL_2 + MC_1+ID_3;           //Start TimerA_0
         P5IES |= BIT6;                           //Flip edge
         P5IE &= ~BIT6;                           //Disable interrupt
         P5IFG &= ~BIT6;                          // P5.6 IFG cleared
  }
  }

  if(P5IFG & BIT5){
  if(P5IES & BIT5){
   TA0CCR0 = 5000;
   TB0CTL = TBSSEL_2 + MC_1+ID_3;                //Start TimerA_0
   P1OUT ^= BIT1;                                //Toggle LEDs
   P5IES &= ~BIT5;                               //Flip edge
   P5IE &= ~BIT5;                                //Disable interrupt
   P5IFG &= ~BIT5;                               // P5.5 IFG cleared
  }
  else{
         TB0CCR0 =5000;
         TB0CTL = TBSSEL_2 + MC_1+ID_3;          //Start TimerA_0
         P5IES |= BIT5;                          //Flip edge
         P5IE &= ~BIT5;                          //Disable interrupt
         P5IFG &= ~BIT5;                         // P5.5 IFG cleared
  }
  }


}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{

   P5IE |=BIT6;                 //Re-enable P5.6 interrupt
   TA0CTL = MC_0;               //Halt TimerA_1
   TA0CTL = TACLR;              //Turn off TimerA_1


}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{

   P5IE |=BIT5;                 //Re-enable P5.5 interrupt
   TB0CTL = MC_0;               //Halt TimerB_1
   TB0CTL = TBCLR;              //Turn off TimerB_1
}



