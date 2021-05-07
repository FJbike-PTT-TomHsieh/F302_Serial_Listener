/*
 * UART_Task.c
 *
 *  Created on: Mar 18, 2021
 *      Author: TomH
 */

#include <stm32f3xx.h>
#include "UART_Task.h"
#include "GPIO_Task.h"
#include "Char_Convert.h"
#include "Speed_Task.h"
#include "Battery_Task.h"

// UART #1 received data resolution task
void UART1_Rec_Task( void )
{

}

// UART #2 received data resolution task
void UART2_Rec_Task( void )
{
	uint8_t temp;

	// Check received count.
	if( uart2_rx_cnt < 5 )
	{
		// Received data too few.
		return;
	}
	// Clear received count.
	uart2_rx_cnt = 0;
	// Resolution received data.
	// Check end character #2.
	if( uart2_rx_data[4] != 0x0a )
	{
		// Not match.
		return;
	}
	// Check end character #2.
	if( uart2_rx_data[3] != 0x0d )
	{
		// Not match.
		return;
	}

	// Check control code.
	if( uart2_rx_data[0] == 0x61 ) // 'a'
	{
		// Update DAC output.
		// high quad.
		temp = Char_to_Int( uart2_rx_data[1] );
		temp <<= 4;
		// low quad.
		temp |= Char_to_Int( uart2_rx_data[2] );
		// Write DAC data.
		DAC1->DHR8R1 = temp;
	}
	else if( uart2_rx_data[0] == 0x62 ) // 'b'
	{
		// Set flag, enable speed data update output.
		speed_flag_enable = 0x01;
		// Clear flag, disable battery update output.
		battery_flag_enable = 0x00;
		// Reset delay count.
		uart2_update_output_delay = 0;
	}
	else if( uart2_rx_data[0] == 0x63 ) // 'c'
	{
		// Clear flag, disable update output speed data.
		speed_flag_enable = 0x00;
		// Set flag, enable battery update output.
		battery_flag_enable = 0x01;
		// Reset delay count.
		uart2_update_output_delay= 0;
	}
	else
	{
		// Clear flag, disable update output speed data.
		speed_flag_enable = 0x00;
		// Clear flag, disable battery update output.
		battery_flag_enable = 0x00;
	}
}

// UART #3 received data resolution task
void UART3_Rec_Task( void )
{

}

// UART #1 data transmit task.
void UART1_Trn_Task( void )
{
	uint32_t temp;

	// Check TX empty flag bit, bit #7.
	temp = USART1->ISR;
	temp &= 0x80;
	if( temp == 0 )
	{
		// Not empty.
		return;
	}
	// Check TX data count.
	if( uart1_tx_cnt == 0 )
	{
		// Check TC flag bit, bit #6.
		temp = USART1->ISR;
		temp &= 0x40;
		if( temp )
		{
			// RS485 receive enable.
			GPIO_UART1_485_RE();
		}

		return;
	}
	else
	{
		// Check status flag bit #0, TX task trigger on.
		temp = uart1_flag;
		temp &= 0x01;
		if( temp )
		{
			// RS485 transmit enable.
			GPIO_UART1_485_DE();
			// Reset index count.
			uart1_tx_index = 0;
			// Reset flag bit.
			uart1_flag &= 0xfe;

			return;
		}
	}

	// Output data via UART.
	USART1->TDR = uart1_tx_data[ uart1_tx_index ];
	// For next byte data.
	--uart1_tx_cnt;
	++uart1_tx_index;
}

// UART #2 data transmit task.
void UART2_Trn_Task( void )
{
	uint32_t temp;

	// Check TX empty flag bit, bit #7.
	temp = USART2->ISR;
	temp &= 0x80;
	if( temp == 0 )
	{
		// Not empty.
		return;
	}

	// Check TX data count.
	if( uart2_tx_cnt == 0 )
	{
		return;
	}
	// Data output via UART.
	USART2->TDR = *ptr_uart2_tx_data;
	// For next byte data.
	--uart2_tx_cnt;
	++ptr_uart2_tx_data;
}

// UART #3 data transmit task.
void UART3_Trn_Task( void )
{
	uint32_t temp;

	// Check TX empty flag bit, bit #7.
	temp = USART3->ISR;
	temp &= 0x80;
	if( temp == 0 )
	{
		// Not empty.
		return;
	}

	// Check TX data count.
	if( uart3_tx_cnt == 0 )
	{
		// Check TC flag bit, bit #6.
		temp = USART3->ISR;
		temp &= 0x40;
		if( temp )
		{
			// RS485 receive enable.
			GPIO_UART3_485_RE();
		}

		return;
	}
	else
	{
		// Check status flag bit #0, TX task trigger on.
		temp = uart3_flag;
		temp &= 0x01;
		if( temp )
		{
			// RS485 transmit enable.
			GPIO_UART3_485_DE();
			// Reset index count.
			uart3_tx_index = 0;
			// Reset flag bit.
			uart3_flag &= 0xfe;

			return;
		}
	}


	// Data output via UART.
	USART3->TDR = uart3_tx_data[ uart3_tx_index ];
	// For next byte data.
	--uart3_tx_cnt;
	++uart3_tx_index;
}

// UART #1 transmit task trigger on.
void UART1_Trn_On( void )
{


	// RS485 transmit enable.
	//GPIO_UART1_485_DE();
	//
	//uart1_tx_index = 0;

}

// UART #2 transmit task trigger on.
void UART2_Trn_On( void )
{
	//
	uart2_tx_index = 0;

}

// UART #3 transmit task trigger on.
void UART3_Trn_On( void )
{
	// RS485 transmit enable.
	GPIO_UART3_485_DE();
	//
	uart3_tx_index = 0;

}

