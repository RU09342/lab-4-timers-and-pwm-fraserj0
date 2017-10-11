#include <msp430fr5994.h>
void HardwarePWM(void){


  // Configure GPIO
    P1OUT &= 0x00;
    P1DIR |= 0x03;                   // P1.2 and P1.3 output

    P1SEL0 |= 0x01;
    P1SEL1 = 0x00;

    P5OUT &= 0x00;                   //Shut everything down
    P5DIR &= 0x00;
    P5DIR |= 0x00;
    P5REN |= BIT6;
    P5OUT |= BIT6;

    P5IE  |= BIT6;                   // P5.6 interrupt enabled
    P5IES |= BIT6;
    P5IFG &= ~BIT6;                  // P5.6 IFG cleared

    TA0CCR0 = 1000-1;                         // PWM Period
    TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TA0CCR1 = 500;                            // CCR1 PWM duty cycle
    TA0CTL = TASSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    __bis_SR_register(LPM0_bits+GIE);             // Enter LPM0
    __no_operation();                         // For debugger
}

 //Port 5 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    unsigned int i;
   if(TA0CCR1 > 1000){
       TA0CCR1 = 0;
   }
   else{
       TA0CCR1 += 100;

   }

   for(i=0;i<32000;i++);                //Delay
   P5IFG &= ~BIT6;                     // P1.3 IFG cleared



}



