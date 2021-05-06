/*
 * Buzzer_Task.h
 *
 *  Created on: Mar 19, 2021
 *      Author: TomH
 */

#ifndef INC_USER_BUZZER_TASK_H_
#define INC_USER_BUZZER_TASK_H_

#include <stdio.h>
#include <stm32f3xx.h>

// Buzzer active delay.
volatile uint32_t bz_dly;

// Initialize.
void Buzzer_Init( void );
// Buzzer turn on.
void Buzzer_On( void );
// Buzzer turn off.
void Buzzer_Off( void );


#endif /* INC_USER_BUZZER_TASK_H_ */
