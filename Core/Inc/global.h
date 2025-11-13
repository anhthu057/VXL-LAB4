/*
 * global.h
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define MODE_NORMAL         1
#define MODE_MODIFY_RED     2
#define MODE_MODIFY_AMBER   3
#define MODE_MODIFY_GREEN   4

#define RED_GREEN           0
#define RED_AMBER           1
#define GREEN_RED           2
#define AMBER_RED           3

extern int current_mode;
extern int traffic_state;

extern int RED_DURATION;
extern int AMBER_DURATION;
extern int GREEN_DURATION;

extern int temp_value;

extern int counter1;
extern int counter2;

extern int blink_state;

#endif /* INC_GLOBAL_H_ */
