/*
 * Buzzer_Task.c
 *
 *  Created on: Mar 19, 2021
 *      Author: TomH
 */

#include <stm32f3xx.h>
#include "Buzzer_Task.h"


// Buzzer turn on.
void Buzzer_On( void )
{
	// PC2 as alternate function mode, bit # 5~ #4, 0x2 .
	GPIOC->MODER &= 0xffffffcf;
	GPIOC->MODER |= 0x00000020;
}

// Buzzer turn off.
void Buzzer_Off( void )
{
	// PC2 ( bit #5 ~ #4 ) as input port mode.
	GPIOC->MODER &= 0xffffffcf;
}

// Initialize.
void Buzzer_Init( void )
{
	// APB2 ( 64MHz ).
	// Timer #1 peripheral clock enable ( bit #11 ).
	RCC->APB2ENR |= 0x00000800;

	TIM1->CR1 = 0x0000;
	// 64MHz = 0.015625us, 15.625ns for DTI .
	// Prescaler value 1.
	TIM1->PSC = 0;
	// Period.
	// 100KHz = 10us.
	// 250us / 0.015625us = 16000.
	TIM1->ARR = 16000;

	// CH #3, PWM duty 50% ( Test ).
	TIM1->CCR3 = 8000;

	// CH #3, configure PWM mode 1.
	TIM1->CCMR2 = 0x00000060;

	// OIS3 = 0, when MOE = 0, ( CH3 and CH3N output state idle ), CH3 output 0,  ( bit #12 ).
	// OIS3N = 1, when MOE = 0, ( CH3 and CH3N output state idle ), CH3N output 1,  ( bit #13 ).
	TIM1->CR2 = 0x00002000;

	// OSSR = 1, When MOE = 0, CH1 / CH1N still output H or L logic, not high Z.  ( it #11 ).
	// AOE = 0, MOE could set/clear by software ( bit #14 ).
	// MOE = 1, Main output ( CH1 and CH1N ) enable, not idle, ( bit #15 ).
	// bit[ 7~0 ] = 8, 8*15.625ns = 125ns dead time.
	TIM1->BDTR = 0x8808;
	// OC #3:
	// Negative output ( TIM1_CH3N ) active low ( bit #11, 0 ).
	// Negative output ( TIM1_CH3N ) enable ( bit #10, 1 ).
	// Positive output ( TIM1_CH3 ) active high ( bit #9, 0 ).
	// Positive output ( TIM1_CH3 ) enable ( bit #8, 1 ).
	TIM1->CCER = 0x0500;
	// Enable.
	TIM1->CR1 |= 0x0001;

	// PC2, alternate function 2, bit #11 ~ #8, 0x02.
	GPIOC->AFR[0] &= 0xfffff0ff;
	GPIOC->AFR[0] |= 0x00000200;

}
