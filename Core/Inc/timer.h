/*
 * timer.h
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#include "scheduler.h"

extern TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIMER_H_ */
