#include "TM4C123.h"
#include <stdint.h>
#include <stdlib.h>
void Delay(unsigned long counter); // used to add delay
void HC05_init(void); // Initialize UART5 module for HC-05
char Bluetooth_Read(void); //Read data from Rx5 pin of TM4C123
void Bluetooth_Write(unsigned char data); // Transmit a character to HC-05 over Tx5 pin 
void Bluetooth_Write_String(char *str); // Transmit a string to HC-05 over Tx5 pin 
int main(void)
{
	  
	HC05_init(); // call HC05_init() to initialze UART5 of TM4C123GH6PM
	
	/* Set PF1, PF2 and PF3 as digital output pins */
	
	SYSCTL->RCGCGPIO |= 0x20;   /* enable clock to GPIOF */
  GPIOF->DIR |= 0x0E;         //set PF1, PF2 and PF3 as digital output pin
  GPIOF->DEN |= 0x0E;         // CON PF1, PF2 and PF3 as digital GPIO pins
	GPIOF->DATA &= 0;
  Delay(5); 
		
	while(1)
	{
		char c = Bluetooth_Read();          /* get a character from UART5 */
		
/* Check the received character and take action to control onboard LEDs of TM4C123 */
/* Send status string to Andriod app after turning on/off LEDs */

     if( c == 'A'){ // refer to the lab manual			 
			GPIOF->DATA |=(1<<3); //write down x
			Bluetooth_Write_String("Green LED ON\n");
		}
		else if( c== 'B'){
			GPIOF->DATA &=~(1<<3); //write down x
			Bluetooth_Write_String("Green LED OFF\n");
		}
		else if( c== 'C'){
			GPIOF->DATA |=(1<<1); //write down x
			Bluetooth_Write_String("Red LED ON\n");
		}
		else if( c== 'D'){
			GPIOF->DATA &=~(1<<1); //write down x
			Bluetooth_Write_String("Red LED OFF\n");
		}
		if( c == 'E'){
			GPIOF->DATA |=(1<<2); //write down x
			Bluetooth_Write_String("Blue LED ON\n");
		}
		else if( c == 'F'){
			GPIOF->DATA &=~(1<<2); // write down x
			Bluetooth_Write_String("Blue LED OFF\n");
		}	
	}
}

/* Dont change the code here*/
void HC05_init(void)
{
	SYSCTL->RCGCUART |= 0x20;  /* enable clock to UART5 */
    SYSCTL->RCGCGPIO |= 0x10;  /* enable clock to PORTE for PE4/Rx and RE5/Tx */
    Delay(1);
    /* UART0 initialization */
    UART5->CTL = 0;         /* UART5 module disbable */
    UART5->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5->CC = 0;          /*select system clock*/
    UART5->LCRH = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
    UART5->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIOE->DEN = 0x30;      /* set PE4 and PE5 as digital */
    GPIOE->AFSEL = 0x30;    /* Use PE4,PE5 alternate function */
    GPIOE->AMSEL = 0;    /* Turn off analg function*/
    GPIOE->PCTL = 0x00110000;     /* configure PE4 and PE5 for UART */
}
char Bluetooth_Read(void)  
{
    char data;
	  while((UART5->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART5->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

void Bluetooth_Write(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}

void Bluetooth_Write_String(char *str)
{
  while(*str)
	{
		Bluetooth_Write(*(str++));
	}
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
}