/*
 * UART_Task.h
 *
 *  Created on: Mar 18, 2021
 *      Author: TomH
 */

#ifndef INC_USER_UART_TASK_H_
#define INC_USER_UART_TASK_H_

#include <stdint.h>

#define FJBSCT_UART1_REC_MAX 16
#define FJBSCT_UART2_REC_MAX 16
#define FJBSCT_UART3_REC_MAX 16

//
volatile uint8_t uart1_flag;
//
volatile uint8_t uart2_flag;
//
volatile uint8_t uart3_flag;


// UART #1 received count.
volatile uint8_t uart1_rx_cnt;
// UART #2 received count.
volatile uint8_t uart2_rx_cnt;
// UART #3 received count.
volatile uint8_t uart3_rx_cnt;

//
volatile uint8_t uart1_tx_cnt;
//
volatile uint8_t uart2_tx_cnt;
//
volatile uint8_t uart3_tx_cnt;

//
volatile uint8_t uart1_tx_index;
//
volatile uint8_t uart2_tx_index;
//
volatile uint8_t uart3_tx_index;


// UART #1 received data holder.
volatile uint8_t uart1_rx_data[ FJBSCT_UART1_REC_MAX + 1 ];
// UART #2 received data holder.
volatile uint8_t uart2_rx_data[ FJBSCT_UART2_REC_MAX + 1 ];
// UART #3 received data holder.
volatile uint8_t uart3_rx_data[ FJBSCT_UART3_REC_MAX + 1 ];

// UART #1 transmit data.
volatile uint8_t uart1_tx_data[ FJBSCT_UART1_REC_MAX + 1 ];
// UART #2 transmit data.
volatile uint8_t uart2_tx_data[ FJBSCT_UART2_REC_MAX + 1 ];
// UART #3 transmit data.
volatile uint8_t uart3_tx_data[ FJBSCT_UART3_REC_MAX + 1 ];

//
volatile uint8_t *ptr_uart2_tx_data;

//
volatile uint32_t uart2_update_output_delay;


// UART #1 received data resolution task
void UART1_Rec_Task( void );
// UART #2 received data resolution task
void UART2_Rec_Task( void );
// UART #3 received data resolution task
void UART3_Rec_Task( void );

// UART #1 data transmit task.
void UART1_Trn_Task( void );
// UART #2 data transmit task.
void UART2_Trn_Task( void );
// UART #3 data transmit task.
void UART3_Trn_Task( void );

// UART #1 transmit task trigger on.
void UART1_Trn_On( void );
// UART #2 transmit task trigger on.
void UART2_Trn_On( void );
// UART #3 transmit task trigger on.
void UART3_Trn_On( void );


#endif /* INC_USER_UART_TASK_H_ */
