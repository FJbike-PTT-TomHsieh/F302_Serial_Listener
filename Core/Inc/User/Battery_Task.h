/*
 * Battery_Task.h
 *
 *  Created on: May 7, 2021
 *      Author: tom Hsieh
 */

#ifndef INC_USER_BATTERY_TASK_H_
#define INC_USER_BATTERY_TASK_H_

#include <stdint.h>

// Flag.
volatile uint8_t battery_flag_enable;
//
volatile uint8_t battery_flag_upout;
// Battery ADC convert value.
volatile uint32_t battery_adc_value;

// Battery check
void Battery_Check( void );
// Battery update output.
void Battery_Update_Output( void );

#endif /* INC_USER_BATTERY_TASK_H_ */
