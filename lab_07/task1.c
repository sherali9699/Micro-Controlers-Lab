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
		A digit -> 0x88
		B digit -> 0x83
		C digit -> 0xC6
		D digit -> 0xA1
		E digit -> 0x86
		F digit -> 0x8E
		OFF digit-> 0xFF
*/


#include "TM4C123GH6PM.h"

int main(void)
{
		unsigned int adc_value;  //Store the ADC Value 0-4095
		unsigned int curr_digit; //Iterator through digitPattern[]
		
		//List of HEX codes for 7-Segment Digits
		unsigned char digitPattern[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
																		0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};  //List of Hex Code for Digits
		
		//PORT B Initialization
		SYSCTL->RCGCGPIO |= (1<<1); //PORT B Clock Active
		GPIOB->DEN = 0xFF;          //PORT B all pins OUTPUT
		GPIOB->DIR = 0xFF;
	
    /* Enable Clock to ADC0 and GPIO pins*/
    SYSCTL->RCGCADC |= (1<<0);    /* AD0 clock enable*/
    
    /* initialize PE3 for AIN0 input  */
		SYSCTL->RCGCGPIO |= (1<<4);   /* Enable Clock to GPIOE or PE3/AN0 */
    GPIOE->AFSEL |= (1<<3);       /* enable alternate function */
    GPIOE->DEN &= ~(1<<3);        /* disable digital function */
    GPIOE->AMSEL |= (1<<3);       /* enable analog function */
   
    /* initialize sample sequencer3 (no bits need to be changed below)*/
    ADC0->ACTSS &= ~(1<<3);        /* disable SS3 during configuration */
    ADC0->EMUX &= ~0xF000;    /* software trigger conversion */
    ADC0->SSMUX3 = 0;         /* get input from channel 0 */
    ADC0->SSCTL3 |= (1<<1)|(1<<2);        /* take one sample at a time, set flag at 1st sample */
    ADC0->ACTSS |= (1<<3);         /* enable ADC0 sequencer 3 */
	 
    while(1)
    {
        ADC0->PSSI |= (1<<3);        		/* Enable SS3 conversion or start sampling data from AN0 */
        while((ADC0->RIS & 8) == 0) ;   /* Wait untill sample conversion completed*/
        adc_value = ADC0->SSFIFO3; 			/* read adc coversion result from SS3 FIFO*/
        ADC0->ISC = 8;          				/* clear coversion clear flag bit*/
			
				/*control Output  */
				//update curr_digit here
				curr_digit = adc_value / 256;
				//use GPIOB->DATA to write value on PORTB 7-Segment from Array based on curr_digit
				GPIOB->DATA = digitPattern[curr_digit];
    }
}
