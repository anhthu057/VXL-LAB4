/*
 * software_timer.c
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#include "software_timer.h"

#define TIMER_CYCLE 10

int timer_counter[MAX_TIMERS];
int timer_flag[MAX_TIMERS];

void setTimer(int index, int duration) {
    if (index >= 0 && index < MAX_TIMERS) {
        timer_counter[index] = duration / TIMER_CYCLE;
        timer_flag[index] = 0;
    }
}

int isTimerExpired(int index) {
    if (index >= 0 && index < MAX_TIMERS) {
        if (timer_flag[index] == 1) {
            timer_flag[index] = 0;
            return 1;
        }
    }
    return 0;
}

void timerRun() {
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] <= 0) {
                timer_flag[i] = 1;
            }
        }
    }
}
