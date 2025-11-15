/*
 * scheduler.c
 *
 *  Created on: Nov 13, 2025
 *      Author: AnhThu
 */

#include "scheduler.h"
#include <string.h>


sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void){
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = NULL;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
    current_index_task = 0;

}

void SCH_Add_Task ( void (*pFunction)(),
					uint32_t DELAY,
					uint32_t PERIOD){
	if (current_index_task >= SCH_MAX_TASKS) return;

	uint8_t i = 0;
	uint32_t d = DELAY;

	// Tìm vị trí để chèn task theo delta-time
	while (i < current_index_task && d > SCH_tasks_G[i].Delay) {
		d -= SCH_tasks_G[i].Delay;  // trừ đi delay của các task trước
		i++;
	}

	// Dịch các task phía sau lên
	for (int j = current_index_task; j > i; j--) {
		SCH_tasks_G[j] = SCH_tasks_G[j - 1];
	}

	// Chèn task mới
	SCH_tasks_G[i].pTask = pFunction;
	SCH_tasks_G[i].Delay = d;
	SCH_tasks_G[i].Period = PERIOD;
	SCH_tasks_G[i].RunMe = 0;
	SCH_tasks_G[i].TaskID = current_index_task;

	// Điều chỉnh Delay của task sau
	if (i < current_index_task) {
		SCH_tasks_G[i + 1].Delay -= d;
	}

	current_index_task++;
}

void SCH_Update(void){
    if (current_index_task == 0) return;
    if (SCH_tasks_G[0].Delay > 0) {
        SCH_tasks_G[0].Delay--;
    }
}

void SCH_Dispatch_Tasks(void){
    while (current_index_task > 0 && SCH_tasks_G[0].Delay == 0) {
        SCH_tasks_G[0].RunMe++;

        // Chạy task
        if (SCH_tasks_G[0].RunMe > 0) {
            SCH_tasks_G[0].RunMe--;
            SCH_tasks_G[0].pTask();
        }

        // Nếu task lặp lại, thêm lại vào mảng
        if (SCH_tasks_G[0].Period > 0) {
            uint32_t period = SCH_tasks_G[0].Period;
            void (*func)() = SCH_tasks_G[0].pTask;

            // Xóa task đầu tiên
            SCH_Delete_Task(0);

            // Thêm lại task lặp vào đúng vị trí
            SCH_Add_Task(func, period, period);
        } else {
            // Xóa task đầu tiên
        	SCH_Delete_Task(0);
        }
    }
}


uint8_t SCH_Delete_Task(uint8_t index) {
    if (index >= current_index_task) {
        return 0; // lỗi: index không hợp lệ
    }

    // Dời các task phía sau lên 1 ô
    for (uint8_t i = index; i < current_index_task - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    current_index_task--;
    return 1; // thành công
}


