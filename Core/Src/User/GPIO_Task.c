/*
 * GPIO_Task.c
 *
 *  Created on: Mar 18, 2021
 *      Author: TomH
 */

#include <stm32f3xx.h>
#include "GPIO_Task.h"
#include "UART_Task.h"
#include "Buzzer_Task.h"

// UART #1 RS485 flow TX on,
void GPIO_UART1_485_DE( void )
{
	// PB1 output high.
	GPIOB->BSRR = 0x00000002;
}

// UART #1 RS485 flow RX on,
void GPIO_UART1_485_RE( void )
{
	// PB1 output low.
	GPIOB->BSRR = 0x00020000;
}

// UART #3 RS485 flow TX on,
void GPIO_UART3_485_DE( void )
{
	// PB2 output high.
	GPIOB->BSRR = 0x00000004;
}

// UART #3 RS485 flow RX on,
void GPIO_UART3_485_RE( void )
{
	// PB2 output low.
	GPIOB->BSRR = 0x00040000;
}

// User LED #1 turn on.
void GPIO_LED1_On( void )
{
	// PC10 output high.
	GPIOC->BSRR = 0x00000400;
}
// User LED #1 turn off.
void GPIO_LED1_Off( void )
{
	// PC10 output low.
	GPIOC->BSRR = 0x04000000;
}

// User LED #2 turn on.
void GPIO_LED2_On( void )
{
	// PC11 output high.
	GPIOC->BSRR = 0x00000800;
}
// User LED #2 turn off.
void GPIO_LED2_Off( void )
{
	// PC11 output low.
	GPIOC->BSRR = 0x08000000;
}

// User LED #3 turn on.
void GPIO_LED3_On( void )
{
	// PC12 output high.
	GPIOC->BSRR = 0x00001000;
}
// User LED #3 turn off.
void GPIO_LED3_Off( void )
{
	// PC12 output low.
	GPIOC->BSRR = 0x10000000;
}


// User LED #4 turn on.
void GPIO_LED4_On( void )
{
	// PD2 output high.
	GPIOD->BSRR = 0x00000004;
}
// User LED #4 turn off.
void GPIO_LED4_Off( void )
{
	// PD2 output low.
	GPIOD->BSRR = 0x00040000;
}

// CAN bus active LED on.
void GPIO_LED_CAN_Active( void )
{
	// PC15 output high.
	GPIOC->BSRR = 0x00008000;
	// Set delay count ( 20 * 10ms ).
	gpio_led_can_dly = 20;
}
// CAN bus inactive LED off.
void GPIO_LED_CAN_Inactive( void )
{
	// PC15 output low.
	GPIOC->BSRR = 0x80000000;
}

// UART #1 active LED on.
void GPIO_LED_UART1_Active( void )
{
	// PC14 output high.
	GPIOC->BSRR = 0x00004000;
	// Set delay count ( 20 * 10ms ).
	gpio_led_uart1_dly = 20;
}

// UART #1 inactive LED off.
void GPIO_LED_UART1_Inactive( void )
{
	// PC14 output low.
	GPIOC->BSRR = 0x40000000;
}

// UART #3 active LED on.
void GPIO_LED_UART3_Active( void )
{
	// PC13 output high.
	GPIOC->BSRR = 0x00002000;
	// Set delay count ( 20 * 10ms ).
	gpio_led_uart3_dly = 20;
}
// UART #3 inactive LED off.
void GPIO_LED_UART3_Inactive( void )
{
	// PC13 output low.
	GPIOC->BSRR = 0x20000000;
}


// Button input task.
void GPIO_Btn_Task( void )
{
	// Read PC5, PC6, PC8, PC9 only.

	uint32_t temp;
	uint32_t current_btn_input;

	// Button debounce count check.
	if( gpio_btn_dbc < 2 )
	{
		// Not done.
		return;
	}
	// Clear count.
	gpio_btn_dbc = 0;

	// Read button input from IO port.
	temp = GPIOC->IDR;
	temp &= 0x00000360;

	// Combine with previous input.
	current_btn_input = gpio_btn_pre;
	current_btn_input |= temp;

	// Keep as previous.
	gpio_btn_pre = temp;

	// Button #1 check.
	if( current_btn_input == 0x0340 )
	{
		// Button hold check.
		temp = gpio_btn_flag;
		temp &= 0x0020;
		if( temp == 0x0020  )
		{
			// Still hold.
			return;
		}
		// Not hold.
		// Set flag bit.
		gpio_btn_flag |= 0x0020;

		// UART #1 test.
		uart1_tx_data[ 0 ] = 0x41;
		uart1_tx_cnt = 1;
		uart1_flag |= 0x01;

		// UART #3 test.
		uart3_tx_data[ 0 ] = 0x41;
		uart3_tx_cnt = 1;
		uart3_flag |= 0x01;

		// Buzzer test.
		Buzzer_On();
		// Keep going 50 * 10ms.
		bz_dly = 20;
	}
	else
	{
		// Button release or no press;
		// Release button status.
		gpio_btn_flag = 0x0000;
	}

}


