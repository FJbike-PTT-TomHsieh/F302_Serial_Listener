/*
 * Timer_Task.h
 *
 *  Created on: Mar 18, 2021
 *      Author: TomH
 */

#ifndef INC_USER_TIMER_TASK_H_
#define INC_USER_TIMER_TASK_H_

#include <stdint.h>

// UART #1 RX timeout count.
volatile uint32_t tmr_uart1_rx_to;
// UART #2 RX timeout count.
volatile uint32_t tmr_uart2_rx_to;
// UART #3 RX timeout count.
volatile uint32_t tmr_uart3_rx_to;

// Time base count, 10ms .
volatile uint32_t time_base_cnt_10ms;

// Timer tick task.
void Timer_Tick( void );


#endif /* INC_USER_TIMER_TASK_H_ */
