#define SYSCTL_RCGCGPIO_R   (*((volatile int *) 0x400FE608))   
#define GPIO_PORTB_DEN_R    (*((volatile int *) 0x4000551C))
#define GPIO_PORTB_DIR_R    (*((volatile int *) 0x40005400))
#define GPIO_PORTB_DATA_R   (*((volatile int *) 0x400053FC))
#define GPIO_PORTB_AMSEL_R  (*((volatile int *) 0x40005528))
#define GPIO_PORTB_AFSEL_R  (*((volatile int *) 0x40005420))
#define GPIO_PORTB_PCTL_R   (*((volatile int *) 0x4000552C))
#define GPIO_PORTB_PUR_R    (*((volatile int *) 0x40005510))
#define GPIO_PORTB_LOCK_R   (*((volatile int *) 0x40005520))
#define GPIO_PORTB_CR_R     (*((volatile int *) 0x40005524))

#include <TM4C123.h>
#define GPIO_PORTB_CLK_EN  0x02      //enable clock for PORTB

void Delay(unsigned int);
void PORTB_Init(void);       //PORTB Initialization function


int main(void)
{
	//Add Hex Code for more digits from the given table in manual inside the list below
	unsigned char digitPattern[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
																	0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};  //List of Hex Code for Digits


	volatile unsigned char i;
	PORTB_Init(); //PORTB Initialization
	
	GPIO_PORTB_DATA_R = digitPattern[i]; //Inital Digit to display on 7-Segment

	while(1)
	{
		//Iterate through digitPattern[] to display "0" - "F" with Delay of 2 Seconds
		for(i = 0; i < 16; i++){
			GPIO_PORTB_DATA_R = digitPattern[i];
			Delay(2000);
		}
		// Use the following command to write digits inside list digitPattern[] on PortB
            // GPIO_PORTB_DATA_R = digitPattern[i];

		//
		//
		//	
	}
}

void Delay(unsigned int delay)
{
	volatile unsigned int i, counter;
	counter = delay * 4000;  // 1 second (1000 msec) needs 40000000 counter so 4000000/1000 = 4000
	for(i=0;i<counter;i++);
}

void PORTB_Init(void)
{
  SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;       // activate clock for Port B
  Delay(10);           													// Delay 10 msec to allow clock to start on PORTB  
  GPIO_PORTB_DEN_R = 0xFF;        	  					// Enable all pins of PORTB 
  GPIO_PORTB_DIR_R = 0xFF;			        	  		// Make all pins of PORTB as ouptut pin
  GPIO_PORTB_PCTL_R &= ~(0xFF) ;					 			// Regular GPIO of PORTB
  GPIO_PORTB_AMSEL_R &= ~(0xFF);        				// Disable analog function on all pins of PORTB
  GPIO_PORTB_AFSEL_R &= ~(0xFF);        				// Regular port function
}
