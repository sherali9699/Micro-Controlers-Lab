#include<TM4C123.h>

void timer0_delay(int ms);

int main()
{
   SYSCTL->RCGCGPIO |= 0x00000020;		// turn on bus clock for GPIOF
   GPIOF->DIR       |= 0x0000000E;		// set RBG pins as digital output pin
   GPIOF->DEN       |= 0x0000000E;		// Enable PF1-3 pinw as digital pin
	
	while (1)
	{
		// implement Traffic Light sequence here
		GPIOF->DATA  = 0x2;    //Turn on RED LED at PF1
		timer0_delay(5000); 	  //Delay in milliseconds
		// ...rest of the logic should go here for traffic system
		GPIOF->DATA = 0x4;  // Blue LED
    timer0_delay(2000);  

		GPIOF->DATA = 0x8;  // Green LED 
		timer0_delay(5000); 
	}
}

void timer0_delay(int ms) // ms is in milliseconds
{
	SYSCTL->RCGCTIMER |= (1<<0);	//enable clock for Timer 0
	
	TIMER0->CTL |= 0x0;		//disable timer 0 before initialization
	TIMER0->CFG =  0x0;		//select configuration for timer 0
	TIMER0->TAMR = 0x1;		//configure timer A for one shot mode
	TIMER0->TAILR = 16000*ms - 1;	//timer A interval load value register
	TIMER0->ICR = 0x1;		//clear status flag
	TIMER0->CTL |= 0x1;		//enable timer 0 to start counting after initializtion
	while ((TIMER0->RIS & 0x1) == 0); //Wait for the GPTM Raw Interrupt Status flag to set
}
