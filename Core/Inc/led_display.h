/*
 * led_display.h
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"
#include "scheduler.h"

void setTrafficLight(int road, int red, int amber, int green);
void clearAllTrafficLights(void);

void display7SEG();

void fsm_normal_mode(void);
void fsm_modify_mode(void);
void fsm_modify_mode_update_display(void);
#endif /* INC_LED_DISPLAY_H_ */
