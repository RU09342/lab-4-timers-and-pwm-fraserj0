### Jake Fraser

## Lab Exercise 4: PWMs and Timers
## Debouncing

## Function
This program uses a combination of a button interrupt and a timer interrupt properly debounce a button in software. This is important 
because using a circuit to hardware debounce can use up precius space on a PCB and cost more for the developer. Since a button is a mechanical system at its core,
 it will bounce a few times when it is pressed. These bounces, depending on how large, can register as the button being pressed multiple times when in fact, the user only pressed it once.
 This could lead to a multitude of issues, including running code before it should be ran, causing the user to be placed in a piece of the program they dont want to be in. Taking care of this issue in software is the most efficient way to fix this common problem.  

## How it works
To fix this issue of button bouncing, the program will essentially tell the processor to not do anything for a set amount of time after the button is pressed. This causes any of the unwanted button bounces to not be processed.
The program starts out by intializing the port 1 registers. The LEDS are initialized to be off and are set as outputs. Since a button is being used, 
a pull up resistor is placed on the corresponding bit. Next, the timer interrupt is initialized, and the CCR is set to 32000. From there, the button ISR is initialized to be triggered whenever the button is pressed. 

Inside the button ISR, the LED is toggled and a timer startes in up mode. Then the interrupt is halted by changing the value of the P1IE register. Because of this,
 the timer will continue counting and immediately enter the timer interrupt upon reaching CCR. Then when the timer interrupt is triggered, the button interrupt is re-enabled and the timer is cleared. Now, the button interrupt is free to continue. Essentially, the button interrupt 
 is halted for 32000 counts until all button buncing is complete. This enables the button to be pressed by the user without worrying about the button bouncing and reaching a line of code that shouldn't have been reached.  

## Usage
Within this project, there are a multitude of files that all use interrupts in a certain manner. In order to run this file, the main.c file needs to be ran.
The user can decide which file they want to run here, and comment out any function that they dont wish to run, leaving the only file to be called, the one they want to run.
Obviously, an error will be given if more than one file is attempted to be called at once. Since there are multiple files in the project that use interrupts, all other files that use the same type of interrupt must be commented out. 
This is because the compiler will recognize both interrupt service routines and an error will ensue. Therefore all files that use the same type of interrupt must be commented out. 
Some of the processors used require various registers to be set. For example some of the processors have LEDs located in port 2, 4, or even 9. The button ports also need to be specified for each processor. Depending on the processor, the timer may also need to be changed.
This information can be found on the datasheet of each processor. 
