/*
 * input_reading.c
 *
 *  Created on: Oct 28, 2025
 *      Author: AnhThu
 */

#include "input_reading.h"
#include "main.h"

#define NO_OF_BUTTONS 3

#define DURATION_FOR_AUTO_INCREASING 100

#define BUTTON_IS_PRESSED GPIO_PIN_SET
#define BUTTON_IS_RELEASED GPIO_PIN_RESET

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

void button_reading(void) {
    for (int i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];

        // Đọc giá trị nút nhấn
        switch(i) {
            case 0:  // BUTTON1
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
                break;
            case 1:  // BUTTON2
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
                break;
            case 2:  // BUTTON3
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
                break;
            default:
            	break;
        }

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
            buttonBuffer[i] = debounceButtonBuffer1[i];

        if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
        	// Nếu một nút được nhấn, chúng ta bắt đầu đếm
            if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                counterForButtonPress1s[i]++;
            } else {
            	// Cờ sẽ bật khi 1 giây trôi qua kể từ khi nút được nhấn
                flagForButtonPress1s[i] = 1;
            }
        } else {
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
    }
}

// Hàm kiểm tra xem nút có được nhấn hay không
unsigned char is_button_pressed(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

// Hàm kiểm tra xem nút có được nhấn đè hay không
unsigned char is_button_pressed_1s(unsigned char index) {
    if (index >= NO_OF_BUTTONS) return 0xff;
    return (flagForButtonPress1s[index] == 1);
}
