#include "TM4C123GH6PM.h"
void Delay_ms(int time_ms);
int duty_cycle = 4999;
void PWM_init(void);
void Turn_AntiClockwise(void);
void Turn_Clockwise(void);
int main(void)
{
   
       PWM_init();
        Turn_Clockwise();
    for(;;)
    {
        duty_cycle = duty_cycle - 10;
        if (duty_cycle <= 0) 
     duty_cycle = 5000;
        PWM1->_3_CMPA = duty_cycle;
        Delay_ms(100);
    }
}
 
 
//Spin motor in one direction by giving IN1 and IN2 signals to L298N
void Turn_Clockwise(void)
{
   SYSCTL->RCGCGPIO |=(1<<5); /* enable clock to PORTF */
    GPIOA->DIR |=(1<<3)||(1<<2);  /* Make PA3 and PA2 an output pin*/
     GPIOA->DEN |=(1<<3)||(1<<2); /* Make PA3 and PA2 an digitally enabled*/
     GPIOA->DATA |=  0x4; /* IN1 Should be HIGH */
   GPIOA->DATA &=  ~0x8; /* IN2 Should be Low*/
}
 
//Spin motor in other direction by giving IN1 and IN2 signals to L298N
 
void Turn_AntiClockwise(void)
{
   SYSCTL->RCGCGPIO |=(1<<5); /* enable clock to PORTF */
    GPIOA->DIR |=(1<<3)||(1<<2);  /* Make PA3 and PA2 an output pin*/
     GPIOA->DEN |=(1<<3)||(1<<2); /* Make PA3 and PA2 an digitally enabled*/
     GPIOA->DATA |=  ~0x4; /* IN1 Should be LOW */
   GPIOA->DATA &=  0x8; /* IN2 Should be HIGH*/
}
 
void PWM_init(void)
{
   
     /* Clock setting for PWM and GPIO PORT */
    SYSCTL->RCGCPWM |= 0x2; /* Enable clock to PWM1 module Page 354 */
    SYSCTL->RCGCGPIO|= (1<<5);/* Enable system clock to PORTF. See page 406 */
   SYSCTL->RCC |= (1<<20);    /* Enable System Clock Divisor function. We want to divide the clock with 64 and set it as the source clock for PWM. See page 254  */
    SYSCTL->RCC |= 0x000E0000; /* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/
 
 /* Setting of PF2 pin for M1PWM6 channel output pin */
    GPIOF->AFSEL |=  (1<<2);      /* PF2 sets a alternate function*/
    GPIOF->PCTL &=  (0x5<<8);/*set PF2 as output pin */
    GPIOF->PCTL |= 0x5<<8; /* make PF2 PWM output pin */
    GPIOF->DEN |= (1<<2);          /* set PF2 as a digital pin */
    
    PWM1->_3_CTL &=  0;  /* Disable Generator 3 counter */
   PWM1->_3_CTL &=   0x4; /* select down count mode of counter 3*/
    PWM1->_3_GENA = (0x3<<2); /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
    PWM1->_3_LOAD = 5000;     /* set load value for 50Hz 16MHz/64 = 250kHz and (250KHz/5000) */
    PWM1->_3_CMPA = 4999;     /* set duty cyle to to minumum value*/
    PWM1->_3_CTL = 1;           /* Enable Generator 3 counter */
    PWM1->ENABLE = 0x40;      /* Enable PWM1 channel 6 output See page Page 1247*/
}
/* This function generates delay in ms */
/* calculations are based on 16MHz system clock frequency */
 
void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}