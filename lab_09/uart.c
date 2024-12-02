#include "TM4C123.h"
#include <stdint.h>
#include <stdlib.h>
void Delay(unsigned long counter);
char UART5_Receiver(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
int main(void)
{
	   /* enable clock to UART5 */
		SYSCTL ->RCGCUART |= 0x20; 
     /* enable clock to PORTE  */
		SYSCTL->RCGCGPIO = 0x10;
    Delay(1);
    /* UART5 initialization: Follow the steps given in the manual under the heading "putting it all together"*/
		UART5->CTL = 0;

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
		GPIOE->AFSEL |= (1<<4) | (1<<5);       /* enable alternate function */
		GPIOE->AMSEL |= (1<<4) | (1<<5);  
		GPIOE->DEN |= (1<<4) | (1<<5);         /* configure digital function */
	  Delay(1); 
	
		UART5->IBRD = 104; // baud rate int part
		UART5->FBRD = 11;  //baud rate fractional part
		UART5->CC = 0x0; // system clock
		UART5->LCRH = (0x70);  //line control register
		UART5->CTL |= (1 << 0) | (1<<8) | (1<<9); // enable the UART again
		GPIOE->PCTL = 0x110000;
	printstring("Hello World \n");
	Delay(10); 
	while(1)
	{
		char c = UART5_Receiver();          /* get a character from UART5 */
		UART5_Transmitter(c); 
	}
}

char UART5_Receiver(void)  
{
  /*Write your code here*/
		while ((UART5->FR & (1 << 4)) != 0); 
		return (char)(UART5->DR & 0xFF);   
}
void UART5_Transmitter(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}
void printstring(char *str)
{
  while(*str)
	{
		UART5_Transmitter(*(str++));
	}
}
void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
}