/*
 * Speed_Task.h
 *
 *  Created on: May 6, 2021
 *      Author: tom hsieh
 */

#ifndef INC_USER_SPEED_TASK_H_
#define INC_USER_SPEED_TASK_H_

#include <stdint.h>

// Sampling count.
#define SPEED_SAMPLE_CNT 5
// 1KM/H timer count for 5cm * 3.1415926
#define SPEED_1KMH_PULSE_COUNT 565486	// microsecond scale.

// update output task flag.
volatile uint8_t speed_flag_enable;
// speed value update task flag.
volatile uint8_t speed_flag_upout;
// sampling data count.
volatile uint8_t speed_sample_cnt;

// Speed sampling timeout count.
volatile uint32_t speed_sample_to;
// timer count value hold, period value.
volatile uint32_t speed_pulse_period[ SPEED_SAMPLE_CNT ];
// timer count value hold, duty value.
volatile uint32_t speed_pulse_duty[ SPEED_SAMPLE_CNT ];
// Current speed.
volatile uint32_t speed_current_value;

// Speed task initialize.
void Speed_Init( void );
// Speed calculate.
void Speed_Calculate( void );
// Speed update output.
void Speed_Update_Output( void );

#endif /* INC_USER_SPEED_TASK_H_ */
