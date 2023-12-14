/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usermain_CM7.h"

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
#define LED_D_Pin GPIO_PIN_5
#define LED_D_GPIO_Port GPIOD
#define V_R2_EN_Pin GPIO_PIN_13
#define V_R2_EN_GPIO_Port GPIOJ
#define BUZ_Pin GPIO_PIN_11
#define BUZ_GPIO_Port GPIOA
#define A_RSEL_Pin GPIO_PIN_7
#define A_RSEL_GPIO_Port GPIOC
#define V_R1_EN_Pin GPIO_PIN_6
#define V_R1_EN_GPIO_Port GPIOC
#define LED_G_Pin GPIO_PIN_12
#define LED_G_GPIO_Port GPIOI
#define LED_O_Pin GPIO_PIN_13
#define LED_O_GPIO_Port GPIOI
#define A_MEAS_Pin GPIO_PIN_8
#define A_MEAS_GPIO_Port GPIOF
#define V_MEAS_Pin GPIO_PIN_4
#define V_MEAS_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
