/*
 * Timer_Task.c
 *
 *  Created on: Mar 18, 2021
 *      Author: TomH
 */

#include "Timer_Task.h"
#include "UART_Task.h"
#include "GPIO_Task.h"
#include "Buzzer_Task.h"

// Timer tick task.
void Timer_Tick( void )
{
	// Check time base count.
	if( time_base_cnt_10ms < 9 )
	{
		// Not done.
		return;
	}
	//
	time_base_cnt_10ms = 0;

	// About 10ms past.

	// Increase button debounce count.
	++gpio_btn_dbc;

	// UART #1 RX timeout check.
	if( uart1_rx_cnt )
	{
		// Not empty.
		// Increase timeout count.
		++tmr_uart1_rx_to;
		// Check received timeout count ( 50 * 10ms ).
		if( tmr_uart1_rx_to == 50 )
		{
			// About 500ms past.
			// Clear count.
			tmr_uart1_rx_to = 0;
			uart1_rx_cnt = 0;
		}
	}

	// UART #2 RX timeout check.
	if( uart2_rx_cnt )
	{
		// Not empty.
		// Increase timeout count.
		++tmr_uart2_rx_to;
		// Check received timeout count ( 200 * 10ms for human key board input ).
		if( tmr_uart2_rx_to == 200 )
		{
			// About 500ms past.
			// Clear count.
			tmr_uart2_rx_to = 0;
			uart2_rx_cnt = 0;
		}
	}

	// UART #3 RX timeout check.
	if( uart3_rx_cnt )
	{
		// Not empty.
		// Increase timeout count.
		++tmr_uart3_rx_to;
		// Check received timeout count ( 50 * 10ms ).
		if( tmr_uart3_rx_to == 50 )
		{
			// About 500ms past.
			// Clear count.
			tmr_uart3_rx_to = 0;
			uart3_rx_cnt = 0;
		}
	}

	// CAN bus active LED.
	if( gpio_led_can_dly )
	{
		--gpio_led_can_dly;
	}
	else
	{
		GPIO_LED_CAN_Inactive();
	}

	// UART #1 active LED.
	if( gpio_led_uart1_dly )
	{
		--gpio_led_uart1_dly;
	}
	else
	{
		GPIO_LED_UART1_Inactive();
	}

	// UART #3 active LED.
	if( gpio_led_uart3_dly )
	{
		--gpio_led_uart3_dly;
	}
	else
	{
		GPIO_LED_UART3_Inactive();
	}

	// Buzzer keep going.
	if( bz_dly )
	{
		// Decrease keep count.
		--bz_dly;
	}
	else
	{
		// Turn off buzzer.
		Buzzer_Off();
	}

}
