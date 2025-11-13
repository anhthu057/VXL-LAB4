/*
 * input_processing.c
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#include "input_processing.h"
#include "global.h"
#include "software_timer.h"
#include "input_reading.h"
#include "led_display.h"
#include "scheduler.h"

enum ButtonState {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_PRESSED_MORE_THAN_1_SECOND
};

enum ButtonState button1State = BUTTON_RELEASED;
enum ButtonState button2State = BUTTON_RELEASED;
enum ButtonState button3State = BUTTON_RELEASED;

// Hàm kiểm tra và điều chỉnh logic thời gian
void adjustTrafficTiming(void) {

    // Quy luật logic: RED = GREEN + AMBER
    int expected_red = GREEN_DURATION + AMBER_DURATION;

    if (RED_DURATION != expected_red) {
        if (current_mode == MODE_MODIFY_RED) {
            // Chỉnh đèn ĐỎ → tự cân đối đèn XANH
            GREEN_DURATION = RED_DURATION - AMBER_DURATION;
            if (GREEN_DURATION < 2) GREEN_DURATION = 2;
        }
        else if (current_mode == MODE_MODIFY_GREEN) {
            // Chỉnh đèn XANH → tính lại đèn ĐỎ
            RED_DURATION = GREEN_DURATION + AMBER_DURATION;
        }
        else if (current_mode == MODE_MODIFY_AMBER) {
            // Chỉnh đèn VÀNG → tính lại đèn ĐỎ
            RED_DURATION = GREEN_DURATION + AMBER_DURATION;
        }
    }

    // Đồng bộ lại biến hiển thị
    counter1 = RED_DURATION;
    counter2 = GREEN_DURATION;
}

void fsm_for_input_processing(void) {
    // BUTTON1
    switch(button1State) {
        // Nếu đang thả, kiểm tra xem có nhấn không
        case BUTTON_RELEASED:
            if(is_button_pressed(0)) {
                button1State = BUTTON_PRESSED;

                // Thay đổi mode
                current_mode++;
                if (current_mode > MODE_MODIFY_GREEN) {
                    current_mode = MODE_NORMAL;
                }

                // Kiểm tra chế độ hiện tại
                switch (current_mode) {
                    case MODE_MODIFY_RED:
                        temp_value = RED_DURATION;
                        break;
                    case MODE_MODIFY_AMBER:
                        temp_value = AMBER_DURATION;
                        break;
                    case MODE_MODIFY_GREEN:
                        temp_value = GREEN_DURATION;
                        break;
                    case MODE_NORMAL:
                        traffic_state = RED_GREEN;
                        counter1 = RED_DURATION;
                        counter2 = GREEN_DURATION;
                        //setTimer(0, 1000);
                        break;
                }
            }
            break;

        // Nếu đang nhấn, kiểm tra có thả ra hay nhấn giữ
        case BUTTON_PRESSED:
            if(!is_button_pressed(0)) {
                button1State = BUTTON_RELEASED;
            } else {
                if(is_button_pressed_1s(0)) {
                    button1State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                }
            }
            break;

        // Nếu đang nhấn giữ, kiểm tra xem có thả ra không
        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if(!is_button_pressed(0)) {
                button1State = BUTTON_RELEASED;
            }
            break;
    }

    // BUTTON2
    if (current_mode != MODE_NORMAL) {
        switch(button2State) {
            case BUTTON_RELEASED:
                if(is_button_pressed(1)) {
                    button2State = BUTTON_PRESSED;
                    // Tăng giá trị thời gian hiển thị
                    temp_value++;
                    if (temp_value > 99) {
                        temp_value = 1;
                    }
                }
                break;

            case BUTTON_PRESSED:
                if(!is_button_pressed(1)) {
                    button2State = BUTTON_RELEASED;
                } else {
                    if(is_button_pressed_1s(1)) {
                        button2State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                    }
                }
                break;

            case BUTTON_PRESSED_MORE_THAN_1_SECOND:
                if(!is_button_pressed(1)) {
                    button2State = BUTTON_RELEASED;
                } else {
                    // Nếu nhấn giữ tăng giá trị mỗi 500ms
                	/*if (isTimerExpired(2)) {
						temp_value++;
						if (temp_value > 99) temp_value = 1;
						setTimer(2, 500);
					}*/
                }
                break;
        }
    }

    // BUTTON3
    if (current_mode != MODE_NORMAL) {
        switch(button3State) {
            case BUTTON_RELEASED:
                if(is_button_pressed(2)) {
                    button3State = BUTTON_PRESSED;

                    // Set giá trị
                    switch (current_mode) {
                        case MODE_MODIFY_RED:
                        	RED_DURATION = temp_value;
                            break;
                        case MODE_MODIFY_AMBER:
                        	AMBER_DURATION = temp_value;
                            break;
                        case MODE_MODIFY_GREEN:
                        	GREEN_DURATION = temp_value;
                            break;
                    }

                    // Kiểm tra logic
                    adjustTrafficTiming();

                    // Trở về chế độ bình thường sau khi thiết lập
                    current_mode = MODE_NORMAL;
                    traffic_state = RED_GREEN;
                    counter1 = RED_DURATION;
                    counter2 = GREEN_DURATION;
                    //setTimer(0, 1000);
                }
                break;

            case BUTTON_PRESSED:
                if(!is_button_pressed(2)) {
                    button3State = BUTTON_RELEASED;
                } else {
                    if(is_button_pressed_1s(2)) {
                        button3State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                    }
                }
                break;

            case BUTTON_PRESSED_MORE_THAN_1_SECOND:
                if(!is_button_pressed(2)) {
                    button3State = BUTTON_RELEASED;
                }
                break;
        }
    }
}

void task_button2_auto_increment(void) {
    // Chỉ chạy nếu ở chế độ modify và nút 2 đang được nhấn giữ
    if (current_mode != MODE_NORMAL && button2State == BUTTON_PRESSED_MORE_THAN_1_SECOND) {
		temp_value++;
		if (temp_value > 99) temp_value = 1;
		// setTimer(2, 500); // Không còn cần thiết, scheduler sẽ tự chạy lại
	}
}
