### Jake Fraser

## Lab Exercise 4: PWMs and Timers
## Hardware PWM

## Function
This program uses hardware to create a pulse width modulator (PWM). When developing this peripheral with hardware, no actual hardware is needed. It simply refers to the lack of timer interrupts in the program. 

PWMs are devices that modulate the amount of time a pulse is on for. In the case of this program, the PWM is designed to adjust the speed at which an LED blinks.
However in this case, the LEDs are blinking fast enough that it actually seems as though the brightness of the LED is affected. An LED blinking faster will
look brighter than an LED that is blinking at a slower rate. This program allows the user to adjust the brightness, through the PWM duty cycle, using a button on board the MSP430 family of processors.
 

## How it works
A PWM is able to vary the time that a signal is high and low for. For example a PWM with a 50% duty cycle is high for 50% of the time
 and low for 50% of the time. In this program, the PWM will start out at 50% duty cycle and each time the button is pressed, the duty cycle will increase by 10%. 
 THis will cause the LED to become 10% brighter with each button press. When the PWM reaches a duty cycle of 100% and the button is pressed,
 it will go back down to 0%.

The program starts out by initializing the P1 registers. Again, since the button is being used, a pull up resistor is placed on the pin with the button. 
Next the driving pin is selected. This is the GPIO pin that the PWM will output onto. To do this, the register P1SEL is set to pin 6, which is the pin that contains LED2 in the case of the MSP430G2553. The pin configurations have been laid out and dealt with accordingly when other processors were used.
From here, a timer is initialized to count in up mode with CCR's of 1000 and 500. This configuration will output a PWM at 50% duty cycle.
 
Whenever the button is pressed, the program runs through a conditional statement. If CCR1 is equal to 1000 (100% duty cycle), then CCR1 is set to 0, effectively bringing the PWM to a 0% percent duty cycle.
If the duty cycle is not at 100%, then the duty cycle is increased by 10%. This is done by adding 100 to the existing value of CCR1. The interrupts used in this program can be seen below.

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

## Usage
Within this project, there are a multitude of files that all use interrupts in a certain manner. In order to run this file, the main.c file needs to be ran.
The user can decide which file they want to run here, and comment out any function that they dont wish to run, leaving the only file to be called, the one they want to run.
Obviously, an error will be given if more than one file is attempted to be called at once. Since there are multiple files in the project that use interrupts, all other files that use the same type of interrupt must be commented out. 
This is because the compiler will recognize both interrupt service routines and an error will ensue. Therefore all files that use the same type of interrupt must be commented out. 
Some of the processors used require various registers to be set. For example some of the processors have LEDs located in port 2, 4, or even 9. The button ports also need to be specified for each processor. Depending on the processor, the timer may also need to be changed.
This information can be found on the datasheet of each processor. 
