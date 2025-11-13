/*
 * input_processing.h
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "global.h"
#include "software_timer.h"
#include "input_reading.h"
#include "scheduler.h"

void adjustTrafficTiming(void);
void fsm_for_input_processing(void);
void task_button2_auto_increment(void);

#endif /* INC_INPUT_PROCESSING_H_ */
