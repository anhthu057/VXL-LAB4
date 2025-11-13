/*
 * timer.c
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#include "timer.h"
#include "software_timer.h"
#include "input_reading.h"
#include "led_display.h"
#include "main.h"
#include "scheduler.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        //timerRun();
    	SCH_Update();
    	button_reading();
    }
}
