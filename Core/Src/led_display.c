/*
 * led_display.c
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#include "led_display.h"
#include "global.h"
#include "main.h"
#include "software_timer.h"
#include "scheduler.h"

static int led_buffer[4] = {0, 0, 0, 0};

void setTrafficLight(int road, int red, int amber, int green) {
    if (road == 0) {
        HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, red ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, amber ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, green ? GPIO_PIN_SET : GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, red ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, amber ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, green ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void clearAllTrafficLights(void) {
    HAL_GPIO_WritePin(GPIOB, RED1_Pin | AMBER1_Pin | GREEN1_Pin |
    		RED2_Pin | AMBER2_Pin | GREEN2_Pin, GPIO_PIN_RESET);
}

void display7SEG() {
	for (int i = 0; i < 4; i++){
		if (led_buffer[i] < 0 || led_buffer[i] > 9) led_buffer[i] = 0;
	}
	HAL_GPIO_WritePin(BCD11_GPIO_Port, BCD11_Pin, (led_buffer[0] & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D0
	HAL_GPIO_WritePin(BCD12_GPIO_Port, BCD12_Pin, (led_buffer[0] & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D1
	HAL_GPIO_WritePin(BCD13_GPIO_Port, BCD13_Pin, (led_buffer[0] & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D2
	HAL_GPIO_WritePin(BCD14_GPIO_Port, BCD14_Pin, (led_buffer[0] & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D3

	HAL_GPIO_WritePin(BCD21_GPIO_Port, BCD21_Pin, (led_buffer[1] & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D0
	HAL_GPIO_WritePin(BCD22_GPIO_Port, BCD22_Pin, (led_buffer[1] & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D1
	HAL_GPIO_WritePin(BCD23_GPIO_Port, BCD23_Pin, (led_buffer[1] & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D2
	HAL_GPIO_WritePin(BCD24_GPIO_Port, BCD24_Pin, (led_buffer[1] & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D3

	HAL_GPIO_WritePin(BCD31_GPIO_Port, BCD31_Pin, (led_buffer[2] & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D0
	HAL_GPIO_WritePin(BCD32_GPIO_Port, BCD32_Pin, (led_buffer[2] & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D1
	HAL_GPIO_WritePin(BCD33_GPIO_Port, BCD33_Pin, (led_buffer[2] & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D2
	HAL_GPIO_WritePin(BCD34_GPIO_Port, BCD34_Pin, (led_buffer[2] & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D3

	HAL_GPIO_WritePin(BCD41_GPIO_Port, BCD41_Pin, (led_buffer[3] & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D0
	HAL_GPIO_WritePin(BCD42_GPIO_Port, BCD42_Pin, (led_buffer[3] & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D1
	HAL_GPIO_WritePin(BCD43_GPIO_Port, BCD43_Pin, (led_buffer[3] & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D2
	HAL_GPIO_WritePin(BCD44_GPIO_Port, BCD44_Pin, (led_buffer[3] & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D3

}

// FSM cho chế độ normal
void fsm_normal_mode(void) {
    //if (isTimerExpired(0)) {
        //setTimer(0, 1000);
		// Cập nhật giá trị hiển thị
	if (current_mode != MODE_NORMAL) return;
	led_buffer[0] = counter1 / 10;
	led_buffer[1] = counter1 % 10;
	led_buffer[2] = counter2 / 10;
	led_buffer[3] = counter2 % 10;

	switch (traffic_state) {

		// Road 1 Đỏ - Road 2 Xanh
		case RED_GREEN:
			// Bật các LED đơn
			setTrafficLight(0, 1, 0, 0);
			setTrafficLight(1, 0, 0, 1);

			counter1--;
			counter2--;
			// Hết thời gian chuyển qua trạng thái tiếp theo
			if (counter2 <= 0) {
				traffic_state = RED_AMBER;
				counter2 = AMBER_DURATION;
			}
			break;

		// Road 1 Đỏ - Road 2 Vàng
		case RED_AMBER:
			setTrafficLight(0, 1, 0, 0);
			setTrafficLight(1, 0, 1, 0);

			counter1--;
			counter2--;
			if (counter2 <= 0) {
				traffic_state = GREEN_RED;
				counter1 = GREEN_DURATION;
				counter2 = RED_DURATION;
			}
			break;

		// Road 1 Xanh - Road 2 Đỏ
		case GREEN_RED:
			setTrafficLight(0, 0, 0, 1);
			setTrafficLight(1, 1, 0, 0);

			counter1--;
			counter2--;
			if (counter1 <= 0) {
				traffic_state = AMBER_RED;
				counter1 = AMBER_DURATION;
			}
			break;

		// Road 1 Vàng - Road 2 Đỏ
		case AMBER_RED:
			setTrafficLight(0, 0, 1, 0);
			setTrafficLight(1, 1, 0, 0);

			counter1--;
			counter2--;
			if (counter1 <= 0) {
				traffic_state = RED_GREEN;
				counter1 = RED_DURATION;
				counter2 = GREEN_DURATION;
			}
			break;
	//}
	}
}

// FSM cho các chế độ sửa đổi
void fsm_modify_mode(void) {
    // Nháy LEDs mỗi 2Hz
    //if (isTimerExpired(1)) {
        //setTimer(1, 250);
	if (current_mode == MODE_NORMAL) {
		//clearAllTrafficLights(); // Tắt đèn khi thoát khỏi chế độ modify
		return;
	}
	blink_state = !blink_state;

	if (blink_state) {
		switch (current_mode) {
			case MODE_MODIFY_RED:
				// Nháy tất cả đèn đỏ
				HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
				break;
			case MODE_MODIFY_AMBER:
				// Nháy tất cả đèn vàng
				HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, GPIO_PIN_SET);
				break;
			case MODE_MODIFY_GREEN:
				// Nháy tất cả đèn xanh
				HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);
				break;
		}
	} else {
		clearAllTrafficLights();
	}
}

void fsm_modify_mode_update_display(void){
	// Chỉ chạy nếu ở một trong các chế độ modify
	if (current_mode == MODE_NORMAL) return;
    // Cập nhật bộ đệm hiển thị
    led_buffer[0] = temp_value / 10;
    led_buffer[1] = temp_value % 10;
    // Hiển thị số thứ tự chế độ
    led_buffer[2] = 0;
    led_buffer[3] = current_mode;
}
