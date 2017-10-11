/**#include <msp430fr5994.h>


void SoftwarePWM(void)
{
    P1OUT &= 0x00;                  //Shut everything down
    P1DIR &= 0x00;
    P1DIR |= 0x03;                  // Set P1.0 and P1.6 to output direction
    P5OUT &= 0x00;                  //Shut Port 5 Down
    P5DIR &= 0x00;
    P5OUT |= BIT6;                  //Select pull-up mode for P5.6
    P5REN |= BIT6;                  // Enable internal pull-up/down resistors
    P5IE |= BIT6;                   // P5.6 interrupt enabled
    P5IES |= BIT6;                  // P5.6 Hi/lo edge
    P5IFG &= ~BIT6;                 // P5.6 IFG cleared


      //Timer A
      TA0CTL |= TAIE;
      TA0CCTL0 |= CCIE;                          // TA0CCR0 interrupt enabled
      TA0CCTL1 |= CCIE;                          //TA0CCR1 interrupt enabled
      TA0CCR0 = 1000;                            //Sets TA0CCR0 to 1000
      TA0CCR1 = 500;
      TA0CTL = TASSEL_2 + MC_1+ID_0;             //Start TimerB_0
      //TB1CTL = TBSSEL_2 + MC_1+ID_0;           //Start TimerB_1

      __bis_SR_register(LPM0_bits + GIE);        // Enter LPM0 w/ interrupt
}
// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    unsigned int i;
   if(TA0CCR1 == 1000){
       TA0CCR1 = 0;
   }
   else{
       TA0CCR1 += 100;

   }

   for(i=0;i<32000;i++);                     //Delay
   P5IFG &= ~BIT6;                           // P5.6 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  P1OUT |= BIT0;

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch(TA0IV){
  case 2:{
      P1OUT &= ~BIT0;
  } break;
 }


}*/



