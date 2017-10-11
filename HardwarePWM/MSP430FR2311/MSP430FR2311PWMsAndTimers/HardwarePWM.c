

#include <msp430fr2311.h>
void HardwarePWM(void){


    // Configure GPIO
    P2DIR |= BIT0 ;
    P2SEL0 |= BIT0;

    P1OUT &= 0x00;                  //Shut everything down
    P1DIR &= 0x00;
    P1DIR |= 0x01;                  // Set P1.0 to output direction
    P1REN |= 0x02;
    P1OUT |= 0x02;

    P1IE  |= 0x02;                  // P1.1 interrupt enabled
    P1IES |= 0x02;
    P1IFG &= ~BIT1;                 // P1.1 IFG cleared

    TB1CCR0 = 1000-1;                         // PWM Period
    TB1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB1CCR1 = 500;                            // CCR1 PWM duty cycle
    TB1CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    __bis_SR_register(LPM0_bits+GIE);             // Enter LPM0
    __no_operation();                         // For debugger
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;
   if(TB1CCR1 > 1000){
       TB1CCR1 = 0;
   }
   else{
       TB1CCR1 += 100;

   }

   for(i=0;i<32000;i++);                //Delay
   P1IFG &= ~BIT1;                     // P1.3 IFG cleared



}
