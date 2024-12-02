#include "TM4C123GH6PM.h"
int main()
{
  SYSCTL->RCGCGPIO |= 0x00000020;		// turn on bus clock for GPIOF
  GPIOF->DIR       |= 0x0000000E;		// set RBG pins as digital output pin
  GPIOF->DEN       |= 0x0000000E;		// Enable PF1-3 pinw as digital pin
	
	SysTick->LOAD = 0x00F42400; 	// one second delay relaod value
	SysTick->CTRL = 0x00000007 ; 	// enable counter, interrupt and select system bus clock 
	SysTick->VAL  = 0; 	//initialize current value register 
   
	while (1)
	{
		//do nothing here since we are using SysTick Interrupt Routine
	}
}


// This Interrupt Service Routine will execute after every one second
void SysTick_Handler(void)
{
   //Use GPIOF->DATA command and toggle PF1-3 pins below between HIGH and LOW
	 GPIOF->DATA ^= 0x0000000E;
}