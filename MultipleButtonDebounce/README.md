### Jake Fraser

## Lab Exercise 4: PWMs and Timers
## Multiple Button Debounce

## Function
This program uses a combination of a button interrupt and timer interrupts to properly debounce two buttons in software. This is important 
because using a circuit to hardware debounce can use up precious space on a PCB and cost more for the developer. Since a button is a mechanical system at its core,
 it will bounce a few times when it is pressed. These bounces, depending on how large, can register as the button being pressed multiple times when in fact, the user only pressed it once.
 This could lead to a multitude of issues, including running code before it should be ran, causing the user to be placed in a piece of the program they dont want to be in. Taking care of this issue in software is the most efficient way to fix this common problem.  

## How it works
To fix this issue of button bouncing, the program will essentially tell the processor to not do anything for a set amount of time after either one of the buttons are pressed. This causes any of the unwanted button bounces to not be processed.
The program starts out by intializing the port 1 registers. The LEDS are initialized to be off and are set as outputs. Since two buttons are being used, 
pull up resistors are placed on bits 5.5 and 5.6. Next, a timer interrupt is initialized for each button, and the CCR is set to 5000. From there, the button ISR is initialized to be triggered whenever the button is pressed. 

Inside the button ISR, a conditional checks to see which button was pressed. In each case, an LED is toggled and a timer starts in up mode. Then the interrupt is halted by changing the value of the P5IE register. Because of this,
 the timer will continue counting and immediately enter the timer interrupt upon reaching CCR. Then when the timer interrupt is triggered, the button interrupt is re-enabled and the timer is cleared. Now, the button interrupt is free to continue. Essentially, the button interrupt 
 is halted for 5000 counts until all button buncing is complete. This enables the button to be pressed by the user without worrying about the button bouncing and reaching a line of code that shouldn't have been reached.  
The ISRs for the buttons and timers can be seen below.

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
  if(P5IFG & BIT6){                     //Check if P5.6 interrupt
  if(P5IES & BIT6){
   TA0CCR0 = 5000;
   TA0CTL = TASSEL_2 + MC_1+ID_3;       //Start TimerA_0
   P1OUT ^= BIT0;                      //Toggle LEDs
   P5IES &= ~BIT6;                      //Flip edge
   P5IE &= ~BIT6;                      //Disable interrupt
   P5IFG &= ~BIT6;                     // P5.6 IFG cleared
  }
  else{
         TA0CCR0 =5000;
         TA0CTL = TASSEL_2 + MC_1+ID_3;       //Start TimerA_0
         P5IES |= BIT6;                       //Flip edge
         P5IE &= ~BIT6;                      //Disable interrupt
         P5IFG &= ~BIT6;                     // P5.6 IFG cleared
  }
  }

  if(P5IFG & BIT5){
  if(P5IES & BIT5){
   TA0CCR0 = 5000;
   TB0CTL = TBSSEL_2 + MC_1+ID_3;       //Start TimerA_0
   P1OUT ^= BIT1;                        //Toggle LEDs
   P5IES &= ~BIT5;                      //Flip edge
   P5IE &= ~BIT5;                      //Disable interrupt
   P5IFG &= ~BIT5;                     // P5.5 IFG cleared
  }
  else{
         TB0CCR0 =5000;
         TB0CTL = TBSSEL_2 + MC_1+ID_3;       //Start TimerA_0
         P5IES |= BIT5;                        //Flip edge
         P5IE &= ~BIT5;                      //Disable interrupt
         P5IFG &= ~BIT5;                     // P5.5 IFG cleared
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

## Usage
 In order to run this file, the main.c file needs to be ran.
The user can decide which file they want to run here, and comment out any function that they dont wish to run, leaving the only file to be called, the one they want to run.
Obviously, an error will be given if more than one file is attempted to be called at once. If there are multiple files in the project that use interrupts, all other files that use the same type of interrupt must be commented out. 
This is because the compiler will recognize both interrupt service routines and an error will ensue. Therefore all files that use the same type of interrupt must be commented out. 
Some of the processors used require various registers to be set. For example some of the processors have LEDs located in port 2, 4, or even 9. The button ports also need to be specified for each processor. Depending on the processor, the timer may also need to be changed.
This information can be found on the datasheet of each processor. 
