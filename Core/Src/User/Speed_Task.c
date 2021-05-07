/*
 * Speed_Task.c
 *
 *  Created on: May 6, 2021
 *      Author: tom hsieh
 */

#include <stm32f3xx.h>
#include "Speed_Task.h"
#include "UART_Task.h"

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
	uint32_t temp3;

	// Check sampling count.
	if( speed_sample_cnt < SPEED_SAMPLE_CNT )
	{
		return;
	}

	// Do not use array #0 data, some times it did not sampling from
	// wheel full a round.

	// For get smallest value from data array.
	temp3 = speed_pulse_period[4];
	// Get average offset.
	temp2 = 0;
	// Set count value.
	cnt = 3;
	while( cnt )
	{
		// Get average delta.
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

		// Get smaller value from array.
		if( temp3 < speed_pulse_period[cnt] )
		{
			temp3 = speed_pulse_period[cnt];
		}

		// Decrease count.
		--cnt;
	}
	// Adjust average offset.
	temp2 >>= 2;
	// Speed pulse count.
	temp3 += temp2;

	// Get current speed.
	if( temp3 > SPEED_1KMH_PULSE_COUNT )
	{
		speed_current_value = 0;
	}
	else
	{
		speed_current_value = SPEED_1KMH_PULSE_COUNT;
		speed_current_value *= 10; // for get 10^-1 digit.
		speed_current_value /= temp3;

		if( speed_current_value > 1000 )
		{
			speed_current_value = 1000;
		}

	}

	// Set flag bit for update output.
	speed_flag_upout = 0x01;
	// Clear count.
	speed_sample_cnt = 0;
}

// Speed update output.
void Speed_Update_Output( void )
{
	uint32_t temp1;

	// UART #2 busy check.
	if( uart2_tx_cnt )
	{
		// Still busy.
		return;
	}

	// Check flag.
	if( speed_flag_enable == 0x00 )
	{
		// Update task not enable.
		return;
	}

	// Check delay count.
	if( uart2_update_output_delay < 150 )
	{
		// Not done.
		return;
	}
	// Reset delay count.
	uart2_update_output_delay = 0;

	if( speed_flag_upout == 0 )
	{
		return;
	}
	// Clear flag.
	speed_flag_upout = 0;

	temp1 = speed_current_value;
	temp1 /= 1000;
	uart2_tx_data[0] = (uint8_t)temp1;
	uart2_tx_data[0] += 0x30; // to character.
	speed_current_value %= 1000;

	temp1 = speed_current_value;
	temp1 /= 100;
	uart2_tx_data[1] = (uint8_t)temp1;
	uart2_tx_data[1] += 0x30; // to character.
	speed_current_value %= 100;

	temp1 = speed_current_value;
	temp1 /= 10;
	uart2_tx_data[2] = (uint8_t)temp1;
	uart2_tx_data[2] += 0x30; // to character.
	speed_current_value %= 10;

	uart2_tx_data[3] = 0x2e; // '.'

	uart2_tx_data[4] = (uint8_t)speed_current_value;
	uart2_tx_data[4] += 0x30; // to character.

	uart2_tx_data[5] = 0x4b; // 'K'
	uart2_tx_data[6] = 0x4d; // 'M'
	uart2_tx_data[7] = 0x2f; // '/'
	uart2_tx_data[8] = 0x48; // 'H'

	uart2_tx_data[9] = 0x0d;
	uart2_tx_data[10] = 0x0a;

	// Prepare UART data output.
	uart2_tx_cnt = 11;
	ptr_uart2_tx_data = uart2_tx_data;
}


