/* Seven Segment Display With Tiva C Launchpad
   As we know that, there are two types of seven segment display (common anode, common cathode) 
   We have used "Common Anode" display in this project.
   When we want to turn on any LED on 7Seg display, the corresponding pin on tivaC should be LOW or 0
   And if i want to turn off any LED on 7Seg display, the corresponding pin on tivaC should be HIGH or 1
	
   We will use GPIOs of PORTB of TivaC to connect our 7-Segment
   Digits on display with pins on Tiva C (Use the following Pin Connection to Connect TivaC with 7-Segment):

	PB7->DP	
	PB6->G	
	PB5->F	
	PB4->E	
	PB3->D	
	PB2->C	
	PB1->B	
	PB0->A   
	3.3V->com(8) (For Common Anode)


		There is a table for each digit on display with corresponding binary and hex formats					
		0 digit <- 1	1	0	0	0	0	0	0 -> 0xC0
		1 digit <- 1	1	1	1	1	0	0	1 -> 0xF9
		2 digit <- 1	0	1	0	0	1	0	0 -> 0xA4
		3 digit <- 1	0	1	1	0	0	0	0 -> 0xB0
		4 digit <- 1	0	0	1	1	0	0	1 -> 0x99
		5 digit <- 1	0	0	1	0	0	1	0 -> 0x92
		6 digit <- 1	0	0	0	0	0	1	0 -> 0x82
		7 digit <- 1	1	1	1	1	0	0	0 -> 0xF8
		8 digit <- 1	0	0	0	0	0	0	0 -> 0x80
		9 digit <- 1	0	0	1	0	0	0	0 -> 0x90
		
*/
		
//Specifying the addresses of the registers below
	
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

#define GPIO_PORTF_DATA_RD 	(*((volatile int *) 0x40025044))
#define GPIO_PORTF_DIR_R  	(*((volatile int *) 0x40025400)) 
#define GPIO_PORTF_DEN_R  	(*((volatile int *) 0x4002551C))
#define GPIO_PORTF_PUR_R 		(*((volatile int *) 0x40025510))
#define GPIO_PORTF_LOCK_R   (*((volatile int *) 0x40025520))
#define GPIO_PORTF_CR_R     (*((volatile int *) 0x40025524))


#define GPIO_PORTF_DATA_R   (*((volatile int *) 0x400253FC)) 
#define GPIO_PORTF_DIR_R    (*((volatile int *) 0x40025400)) 
#define GPIO_PORTF_DEN_R    (*((volatile int *) 0x4002551C)) 
#define GPIO_PORTF_AFSEL_R  (*((volatile int *) 0x40025420)) 
#define GPIO_PORTF_PCTL_R   (*((volatile int *) 0x4002552C)) 
#define GPIO_PORTF_AMSEL_R  (*((volatile int *) 0x40025528)) 
#define GPIO_PORTF_PUR_R    (*((volatile int *) 0x40025510)) 
#define GPIO_PORTF_LOCK_R   (*((volatile int *) 0x40025520)) 

#define GPIO_PORT_CLK_EN  0x22      /* enable clock for PORTB and PORTF*/

#define SYSTEM_CLOC_FREQUENCY  16000000

#define DELAY_DEBOUNCE   SYSTEM_CLOC_FREQUENCY/4000000

void Delay(unsigned int);
void PORTB_Init(void);			//PORTB Initialization function
void PORTF_Init(void);			//PORTF Initialization function

int main(void)
{
	//Declare your list here and initialize PortB and PortF here
  unsigned char digitPattern[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
																	0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};  //List of Hex Code for Digits

	PORTB_Init();
	PORTF_Init();
	
	volatile unsigned int i = 0;
	
	GPIO_PORTB_DATA_R = digitPattern[0];																
	
	while(1)
	{
	//Use the following command to read SW1 State (0 means pressed)
	// (GPIO_PORTF_DATA_RD & 0x10) == 0
	//Use the following command to read SW2 State (0 means pressed)
	// (GPIO_PORTF_DATA_RD & 0x01) == 0
      // Write your code below to read state of SW1/SW2 and write on 7-Segment
		if((GPIO_PORTF_DATA_RD & 0x10) == 0){			
				Delay(200);
			  if(i < 15){i++;}
				else {i = 0;}
				GPIO_PORTB_DATA_R = digitPattern[i];
			}
		else if (((GPIO_PORTF_DATA_RD & 0x01) == 0)){
				Delay(200);
				if(i > 0){i--;}
				else {i = 15;}
				GPIO_PORTB_DATA_R = digitPattern[i];
				
		   }	
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
	SYSCTL_RCGCGPIO_R |= GPIO_PORT_CLK_EN;            // activate clock for Port B and F
  Delay(10);           															// Delay 10 msec to allow clock to start on PORTs  
  GPIO_PORTB_DEN_R = 0xFF;        	  							// Enable all pins of PORTB
  GPIO_PORTB_DIR_R = 0xFF;        	  							// Make all pins of PORTB as ouptut pin
	GPIO_PORTB_PCTL_R &= ~(0xFF) ; 										// Regular GPIO of PORTB
  GPIO_PORTB_AMSEL_R &= ~(0xFF);        						// Disable analog function on all pins of PORTB
	GPIO_PORTB_AFSEL_R &= ~(0xFF);        						// Regular port function
													// Configure PORTF Pins as input pins
	
	GPIO_PORTF_DEN_R = 0xFF;                         
  GPIO_PORTF_DIR_R &= ~(0xFF);                     
  GPIO_PORTF_PCTL_R &= ~(0xFF);                    
  GPIO_PORTF_AMSEL_R &= ~(0xFF);                   
  GPIO_PORTF_AFSEL_R &= ~(0xFF);
}


void PORTF_Init(void)
{
GPIO_PORTF_LOCK_R = 0x4C4F434B;   								  // unlockGPIOFCR register
	GPIO_PORTF_CR_R = 0x11; 													// enable commits for F0 and F4
	GPIO_PORTF_PUR_R |= 0x11;													// Pull up resistor for F0 and F4
	GPIO_PORTF_LOCK_R = 0x00; 			  								// lockGPIOFCR register
	GPIO_PORTF_DEN_R  = 0xFF;  												// Enable PORTF
	GPIO_PORTF_DIR_R  = 0x00;  
}