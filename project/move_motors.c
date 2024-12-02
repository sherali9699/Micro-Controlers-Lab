#include "TM4C123GH6PM.h"
void Delay_ms(int time_ms);
int duty_cycle = 4999;
void PWM_init(void);
void Turn_AntiClockwise(void);
void Turn_Clockwise(void);
void Turn_Clockwise_Motor_2(void);
void Turn_AntiClockwise_Motor_2(void);
void PWM_init_2(void);
void PWM_init_dual_motor(void);
int main(void)
{
   
    //PWM_init();
	//PWM_init_2();
	PWM_init_dual_motor();
    Turn_Clockwise(); // // FOR FRONT DIRECTION OF THIS MOTOR (RIGHT)
    //Turn_AntiClockwise();
    //Turn_Clockwise_Motor_2();
	Turn_AntiClockwise_Motor_2(); // FOR FRONT DIRECTION OF THIS MOTOR (LEFT)
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
    SYSCTL->RCGCGPIO = 0x20; 			/* enable clock to PORTF */
    SYSCTL->RCGCGPIO |= 0x01;  
    GPIOA->DIR |= (1 << 3) | (1 << 2);  /* Make PA3 and PA2 output pins */
    GPIOA->DEN |= (1 << 3) | (1 << 2);  /* Enable PA3 and PA2 digitally */
    GPIOA->DATA |= 0x4;                 /* Set IN1 (PA2) HIGH */
    GPIOA->DATA &= ~0x8;                /* Set IN2 (PA3) LOW */
}

void Turn_Clockwise_Motor_2(void)
{
    SYSCTL->RCGCGPIO = 0x20; 			/* enable clock to PORTF */
    SYSCTL->RCGCGPIO |= 0x01;  
    GPIOA->DIR |= (1 << 6) | (1 << 7);  /* Make PA6 and PA7 output pins */
    GPIOA->DEN |= (1 << 6) | (1 << 7);  /* Enable PA6 and PA7 digitally */
    GPIOA->DATA |= 0x40;                /* Set IN3 (PA6) HIGH */
    GPIOA->DATA &= ~0x80;               /* Set IN4 (PA7) LOW */
}

//Spin motor in other direction by giving IN1 and IN2 signals to L298N

void Turn_AntiClockwise(void)
{
    SYSCTL->RCGCGPIO |= (1 << 5);       /* Enable clock to PORTF */
    SYSCTL->RCGCGPIO |= 0x01;
    GPIOA->DIR |= (1 << 3) | (1 << 2);  /* Make PA3 and PA2 output pins */
    GPIOA->DEN |= (1 << 3) | (1 << 2);  /* Enable PA3 and PA2 digitally */
    GPIOA->DATA &= ~0x4;                /* Set IN1 (PA2) LOW */
    GPIOA->DATA |= 0x8;                 /* Set IN2 (PA3) HIGH */
}

void Turn_AntiClockwise_Motor_2(void)
{
    SYSCTL->RCGCGPIO |= (1 << 5);       /* Enable clock to PORTF */
    SYSCTL->RCGCGPIO |= 0x01;
    GPIOA->DIR |= (1 << 6) | (1 << 7);  /* Make PA6 and PA7 output pins */
    GPIOA->DEN |= (1 << 6) | (1 << 7);  /* Enable PA6 and PA7 digitally */
    GPIOA->DATA &= ~0x40;               /* Set IN3 (PA6) LOW */
    GPIOA->DATA |= 0x80;                /* Set IN4 (PA7) HIGH */
}

void PWM_init(void)
{
   
     /* Clock setting for PWM and GPIO PORT */
    SYSCTL->RCGCPWM = 0x2; /* Enable clock to PWM1 module Page 354 */
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

void PWM_init_2(void)
{
    /* Clock setting for PWM and GPIO PORT */
    SYSCTL->RCGCPWM |= 0x2;           /* Enable clock to PWM1 module */
    SYSCTL->RCGCGPIO |= (1 << 5);     /* Enable system clock to PORTF */
    SYSCTL->RCC |= (1 << 20);         /* Enable System Clock Divisor function */
    SYSCTL->RCC |= 0x000E0000;        /* Use a pre-divider value of 64 */

    /* Setting of PF3 pin for M1PWM7 channel output pin */
    GPIOF->AFSEL |= (1 << 3);         /* Set PF3 as alternate function */
    GPIOF->PCTL &= ~(0xF << 12);      /* Clear PCTL bits for PF3 */
    GPIOF->PCTL |= (0x5 << 12);       /* Set PF3 to M1PWM7 */
    GPIOF->DEN |= (1 << 3);           /* Set PF3 as a digital pin */

    PWM1->_3_CTL = 0;                 /* Disable Generator 3 counter */
    PWM1->_3_CTL &= ~0x4;             /* Select down-count mode for Generator 3 */
    PWM1->_3_GENA = (0x3 << 2);       /* Set PWM output when counter is reloaded and clear when matches PWMCMPA */
    PWM1->_3_LOAD = 5000;             /* Set load value for 50Hz (16MHz/64 = 250kHz, so 250KHz/5000) */
    PWM1->_3_CMPA = 4999;             /* Set initial duty cycle to minimum */
    PWM1->_3_CTL |= 1;                /* Enable Generator 3 counter */
    PWM1->ENABLE = 0x80;              /* Enable PWM1 channel 7 output */
}

void PWM_init_dual_motor(void)
{
    // Enable clock for PWM1 and Port F
    SYSCTL->RCGCPWM |= 0x2;             // Enable clock to PWM1 module
    SYSCTL->RCGCGPIO |= (1 << 5);       // Enable system clock to PORTF
    SYSCTL->RCC |= (1 << 20) | 0x000E0000; // Enable System Clock Divisor function with a pre-divider of 64
 
    // Configure PF2 (PWM6) for Motor 1
    GPIOF->AFSEL |= (1 << 2);           // Set PF2 for alternate function
    GPIOF->PCTL &= ~(0xF << 8);         // Clear PCTL bits for PF2
    GPIOF->PCTL |= (0x5 << 8);          // Set PF2 to M1PWM6
    GPIOF->DEN |= (1 << 2);             // Set PF2 as a digital pin
 
    // Configure PF3 (PWM7) for Motor 2
    GPIOF->AFSEL |= (1 << 3);           // Set PF3 for alternate function
    GPIOF->PCTL &= ~(0xF << 12);        // Clear PCTL bits for PF3
    GPIOF->PCTL |= (0x5 << 12);         // Set PF3 to M1PWM7
    GPIOF->DEN |= (1 << 3);             // Set PF3 as a digital pin
 
    // Configure Generator 3 for down-count mode
    PWM1->_3_CTL = 0;                   // Disable Generator 3 for configuration
    PWM1->_3_GENA = (0x3 << 2);         // Set PWM6 output on reload and clear on CMPA match
    PWM1->_3_GENB = (0x3 << 2);         // Set PWM7 output on reload and clear on CMPB match
    PWM1->_3_LOAD = 5000;               // Set load value for 50Hz (16MHz/64 = 250kHz, so 250KHz/5000)
    // Set initial duty cycles
    PWM1->_3_CMPA = 4000;               // Set duty cycle for PWM6 (Motor 1)
    PWM1->_3_CMPB = 3000;               // Set duty cycle for PWM7 (Motor 2)
    PWM1->_3_CTL = 1;                   // Enable Generator 3
    PWM1->ENABLE |= (0x40 | 0x80);      // Enable PWM1 channel 6 (PWM6) and channel 7 (PWM7)
}


void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}