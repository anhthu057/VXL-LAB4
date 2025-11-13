/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON1_Pin GPIO_PIN_1
#define BUTTON1_GPIO_Port GPIOA
#define BUTTON2_Pin GPIO_PIN_2
#define BUTTON2_GPIO_Port GPIOA
#define BUTTON3_Pin GPIO_PIN_3
#define BUTTON3_GPIO_Port GPIOA
#define BCD11_Pin GPIO_PIN_4
#define BCD11_GPIO_Port GPIOA
#define BCD12_Pin GPIO_PIN_5
#define BCD12_GPIO_Port GPIOA
#define BCD13_Pin GPIO_PIN_6
#define BCD13_GPIO_Port GPIOA
#define BCD14_Pin GPIO_PIN_7
#define BCD14_GPIO_Port GPIOA
#define RED1_Pin GPIO_PIN_0
#define RED1_GPIO_Port GPIOB
#define AMBER1_Pin GPIO_PIN_1
#define AMBER1_GPIO_Port GPIOB
#define GREEN1_Pin GPIO_PIN_2
#define GREEN1_GPIO_Port GPIOB
#define ROW4_Pin GPIO_PIN_12
#define ROW4_GPIO_Port GPIOB
#define ROW5_Pin GPIO_PIN_13
#define ROW5_GPIO_Port GPIOB
#define ROW6_Pin GPIO_PIN_14
#define ROW6_GPIO_Port GPIOB
#define ROW7_Pin GPIO_PIN_15
#define ROW7_GPIO_Port GPIOB
#define BCD21_Pin GPIO_PIN_8
#define BCD21_GPIO_Port GPIOA
#define BCD22_Pin GPIO_PIN_9
#define BCD22_GPIO_Port GPIOA
#define BCD23_Pin GPIO_PIN_10
#define BCD23_GPIO_Port GPIOA
#define BCD24_Pin GPIO_PIN_11
#define BCD24_GPIO_Port GPIOA
#define BCD31_Pin GPIO_PIN_12
#define BCD31_GPIO_Port GPIOA
#define BCD32_Pin GPIO_PIN_13
#define BCD32_GPIO_Port GPIOA
#define BCD33_Pin GPIO_PIN_14
#define BCD33_GPIO_Port GPIOA
#define BCD34_Pin GPIO_PIN_15
#define BCD34_GPIO_Port GPIOA
#define RED2_Pin GPIO_PIN_3
#define RED2_GPIO_Port GPIOB
#define AMBER2_Pin GPIO_PIN_4
#define AMBER2_GPIO_Port GPIOB
#define GREEN2_Pin GPIO_PIN_5
#define GREEN2_GPIO_Port GPIOB
#define BCD41_Pin GPIO_PIN_6
#define BCD41_GPIO_Port GPIOB
#define BCD42_Pin GPIO_PIN_7
#define BCD42_GPIO_Port GPIOB
#define BCD43_Pin GPIO_PIN_8
#define BCD43_GPIO_Port GPIOB
#define BCD44_Pin GPIO_PIN_9
#define BCD44_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
