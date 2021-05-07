/*
 * Battery_Task.c
 *
 *  Created on: May 7, 2021
 *      Author: tom hsieh
 */

#include <stm32f3xx.h>
#include "Battery_Task.h"
#include "UART_Task.h"

// Battery check
void Battery_Check( void )
{
	uint32_t temp;

	// Check ADC ready flag bit.
	temp = ADC1->CR;
	temp &= 0x00000004;
	if( temp )
	{
		// Still busy.
		return;
	}

	// Keep ADC converted value.
	battery_adc_value = ADC1->DR;

	battery_adc_value *= 33;
	battery_adc_value *= 145;
	battery_adc_value >>= 12;

	// Start new convert.
	ADC1->CR |= 0x00000004;

	// Set data update flag.
	battery_flag_upout = 1;
}

// Battery update output.
void Battery_Update_Output( void )
{
	uint32_t temp1;

	// UART #2 busy check.
	if( uart2_tx_cnt )
	{
		// Still busy.
		return;
	}

	// Check flag.
	if( battery_flag_enable == 0x00 )
	{
		// Update task not enable.
		return;
	}

	// Check delay count.
	if( uart2_update_output_delay < 150 )
	{
		return;
	}
	// Reset delay count.
	uart2_update_output_delay = 0;

	if( battery_flag_upout == 0 )
	{
		return;
	}
	// Clear flag.
	battery_flag_upout = 0;


	temp1 = battery_adc_value;
	temp1 /= 1000;
	uart2_tx_data[0] = (uint8_t)temp1;
	uart2_tx_data[0] += 0x30; // to character.
	battery_adc_value %= 1000;

	temp1 = battery_adc_value;
	temp1 /= 100;
	uart2_tx_data[1] = (uint8_t)temp1;
	uart2_tx_data[1] += 0x30; // to character.
	battery_adc_value %= 100;

	uart2_tx_data[2] = 0x2e; // '.'

	temp1 = battery_adc_value;
	temp1 /= 100;
	uart2_tx_data[3] = (uint8_t)temp1;
	uart2_tx_data[3] += 0x30; // to character.
	battery_adc_value %= 100;

	uart2_tx_data[4] = 0x56; // 'V'

	uart2_tx_data[5] = 0x0d;
	uart2_tx_data[6] = 0x0a;

	// Prepare UART data output.
	uart2_tx_cnt = 7;
	ptr_uart2_tx_data = uart2_tx_data;
}
