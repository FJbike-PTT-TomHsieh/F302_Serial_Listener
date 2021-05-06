/*
 * Speed_Task.h
 *
 *  Created on: May 6, 2021
 *      Author: tom hsieh
 */

#ifndef INC_USER_SPEED_TASK_H_
#define INC_USER_SPEED_TASK_H_

#include <stdint.h>

#define SPEED_SAMPLE_CNT 5

// sample count.
volatile uint8_t speed_sample_cnt;
// timer count value hold, period value.
volatile uint32_t speed_pulse_period[ SPEED_SAMPLE_CNT ];
// timer count value hold, duty value.
volatile uint32_t speed_pulse_duty[ SPEED_SAMPLE_CNT ];


// Speed task initialize.
void Speed_Init( void );
// Speed calculate.
void Speed_Calculate( void );


#endif /* INC_USER_SPEED_TASK_H_ */
