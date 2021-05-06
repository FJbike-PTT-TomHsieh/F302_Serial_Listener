/*
 * Speed_Task.c
 *
 *  Created on: May 6, 2021
 *      Author: tom hsieh
 */

#include <stm32f3xx.h>
#include "Speed_Task.h"

// Speed task initialize.
void Speed_Init( void )
{
	// APB2 ( 64MHz ).
	// Timer #2 peripheral clock enable ( bit #1 = 1 ).
	RCC->APB1ENR |= 0x00000001;

	// Prescaler value 1.
	TIM2->PSC = 63;

	// CC1S = 0x1, ( bit #1 ~ 0, 0x1 )
	// CC2S = 0x2, ( bit #9 ~ 8, 0x2 )
	TIM2->CCMR1 |= 0x00000201;

	// CC2NP = 0, ( bit #7, 0 ).
	// CC2P = 1, ( bit #5, 1 ).
	// CC1NP = 1, ( bit #3, 1 ).
	// CC1P = 0, ( bit #1, 0 ).
	TIM2->CCER = 0x00000028;

	// TS = 0x5, ( bit #6 ~ 4, 0x5 )
	// SMS = 0x4, ( bit #16, #2~0, 0x4 )
	TIM2->SMCR = 0x00000054;

	// CC2E = 1 ( bit #4 ).
	// CC1E = 1 ( bit #0 ).
	TIM2->CCER |= 0x00000011;

	// Enable CC1 interrupt.
	TIM2->DIER |= 0x02;
	// Enable IRQ.
	NVIC_EnableIRQ( TIM2_IRQn );
	// Enable timer #2 ( bit #0, 1 ).
	TIM2->CR1 |= 0x0001;
}

// Speed calculate.
void Speed_Calculate( void )
{
	//uint8_t delta_sign;

	uint8_t cnt;
	uint32_t temp1;
	uint32_t temp2;

	// Check sampling count.
	if( speed_sample_cnt < SPEED_SAMPLE_CNT )
	{
		return;
	}

	// Do not use array #0 data, some times it did not sampling from
	// wheel full a round.

	// Get offset.
	temp2 = 0;
	cnt = 3;
	while( cnt )
	{
		temp1 = speed_pulse_period[4];

		if( temp1 >= speed_pulse_period[cnt] )
		{
			temp1 -= speed_pulse_period[cnt];
		}
		else
		{
			temp1 = speed_pulse_period[cnt];
			temp1 -= speed_pulse_period[4];
		}
		temp2 += temp1;
		--cnt;
	}
	// average offset.
	temp2 >>= 2;

	// Get smallest value for data array.
	temp1 = speed_pulse_period[4];
	cnt = 3;
	while( cnt )
	{
		if( temp1 < speed_pulse_period[cnt] )
		{
			temp1 = speed_pulse_period[cnt];
		}
		--cnt;
	}
	// Speed pulse count.
	temp1 += temp2;


	// Clear count.
	speed_sample_cnt = 0;
}

