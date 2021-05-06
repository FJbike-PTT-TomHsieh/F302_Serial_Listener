/*
 * GPIO_Task.h
 *
 *  Created on: Mar 18, 2021
 *      Author: TomH
 */

#ifndef INC_USER_GPIO_TASK_H_
#define INC_USER_GPIO_TASK_H_

#include <stdint.h>

// Debounce count.
volatile uint32_t gpio_btn_dbc;
// Previous button input status.
volatile uint32_t gpio_btn_pre;

//
volatile uint32_t gpio_led_can_dly;
//
volatile uint32_t gpio_led_uart1_dly;
//
volatile uint32_t gpio_led_uart3_dly;

//
volatile uint32_t gpio_btn_flag;


// UART #1 RS485 flow TX on,
void GPIO_UART1_485_DE( void );
// UART #1 RS485 flow RX on,
void GPIO_UART1_485_RE( void );

// UART #3 RS485 flow TX on,
void GPIO_UART3_485_DE( void );
// UART #3 RS485 flow RX on,
void GPIO_UART3_485_RE( void );

// User LED #1 turn on.
void GPIO_LED1_On( void );
// User LED #1 turn off.
void GPIO_LED1_Off( void );

// User LED #2 turn on.
void GPIO_LED2_On( void );
// User LED #2 turn off.
void GPIO_LED2_Off( void );

// User LED #3 turn on.
void GPIO_LED3_On( void );
// User LED #3 turn off.
void GPIO_LED3_Off( void );

// User LED #4 turn on.
void GPIO_LED4_On( void );
// User LED #4 turn off.
void GPIO_LED4_Off( void );

// CAN bus active LED on.
void GPIO_LED_CAN_Active( void );
// CAN bus inactive LED off.
void GPIO_LED_CAN_Inactive( void );

// UART #1 active LED on.
void GPIO_LED_UART1_Active( void );
// UART #1 inactive LED off.
void GPIO_LED_UART1_Inactive( void );

// UART #3 active LED on.
void GPIO_LED_UART3_Active( void );
// UART #3 inactive LED off.
void GPIO_LED_UART3_Inactive( void );


// Button input task.
void GPIO_Btn_Task( void );


#endif /* INC_USER_GPIO_TASK_H_ */
