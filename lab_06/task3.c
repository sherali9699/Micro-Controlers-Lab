#include<TM4C123.h>

void timer1a_pwm(int duty_cycle);
void timer2a_pwm(int duty_cycle);
void timer3a_pwm(int duty_cycle);
void timer0_delay(int ms);

int main()
{
	SYSCTL->RCGCTIMER |= 0x0F;	//enable clock for Timer 0-3
	SYSCTL->RCGCGPIO |= (1<<1);      /* enable clock to PORTB  */
	
	// Initialize Channel Timer 1A PWM to PB4
	GPIOB->DIR |= (1<<4);   /* set PB4 an output pin */
	GPIOB->DEN |= (1<<4);    /* set PB4 a digital pin */
	GPIOB->AFSEL |= (1<<4);  /* enable alternate function on PB4 */
	GPIOB->PCTL &= ~0x000F0000;  /* configure PB4 as T1CCP0 pin */
	GPIOB->PCTL |= 0x00070000;
	
	// Initialize Channel Timer 2A PWM to PB0
	GPIOB->DIR |= (1 << 0);
	GPIOB->DEN |= (1 << 0);       
  GPIOB->AFSEL |= (1 << 0);    
  GPIOB->PCTL &= ~0x0000000F;    
  GPIOB->PCTL |= 0x00000007; 
	
	// Initialize Channel Timer 3A PWM to PB2
	GPIOB->DIR |= (1 << 2);    
  GPIOB->DEN |= (1 << 2);     
  GPIOB->AFSEL |= (1 << 2);      
  GPIOB->PCTL &= ~0x00000F00;  
  GPIOB->PCTL |= 0x00000700; 
	
	// Use PWM functions to output RGB Color spectrum using dutycycles calculated with your ID
	int id1 = 10;
	int id2 = 70;
	int id3 = 10;

	timer1a_pwm(id1);
	timer2a_pwm(id2);
	timer3a_pwm(id3);

	while (1)
	{
		// Do nothing OR Write a logic to toggle color spectrum using timer0 delay
					
	}
}

void timer1a_pwm(int duty_cycle) //duty cycle range: 0 - 100 %
{
	TIMER1->CTL |= 0x0;						//disable timer before initialization
	TIMER1->CFG = 0x4;						//select 16-bit configuration
	TIMER1->TAMR |= (1 << 3);			//TAAMS set to 0x1 to enable PWM mode
	TIMER1->TAMR &= ~(1UL << 2);	//TACMR reset to 0 for Edge Count Mode
	TIMER1->TAMR |= (2 << 0);			//TAMR set to 0x2 for periodic timer mode
	TIMER1->TAILR = 16000 - 1;		// 1ms period | interval load value register
	TIMER1->TAMATCHR = 160 * duty_cycle;	// cut-off edge to control PWM duty cycle
	TIMER1->CTL |= 0x1;						//enable timer to start counting after initializtion
}

void timer2a_pwm(int duty_cycle) //duty cycle range: 0 - 100 %
{
	//Initialize TIMER2 here
	TIMER2->CTL |= 0x0;                
	TIMER2->CFG = 0x4;                 
	TIMER2->TAMR |= (1 << 3);        
	TIMER2->TAMR &= ~(1UL << 2);
	TIMER2->TAMR |= (2 << 0);              
	TIMER2->TAILR = 16000 - 1;             
	TIMER2->TAMATCHR = 160 * duty_cycle;
  TIMER2->CTL |= 0x1; 
}

void timer3a_pwm(int duty_cycle) //duty cycle range: 0 - 100 %
{
	//Initialize TIMER3 here
	TIMER3->CTL |= 0x0;                
	TIMER3->CFG = 0x4;                 
	TIMER3->TAMR |= (1 << 3);        
	TIMER3->TAMR &= ~(1UL << 2);
	TIMER3->TAMR |= (2 << 0);              
	TIMER3->TAILR = 16000 - 1;             
	TIMER3->TAMATCHR = 160 * duty_cycle;
  TIMER3->CTL |= 0x1; 
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

