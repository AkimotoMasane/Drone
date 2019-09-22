/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define LPS22HB_CS_Pin GPIO_PIN_13
#define LPS22HB_CS_GPIO_Port GPIOC
#define USB_Monitor_Pin GPIO_PIN_14
#define USB_Monitor_GPIO_Port GPIOC
#define Reserved_Pin GPIO_PIN_15
#define Reserved_GPIO_Port GPIOC
#define BLE_IRQ_Pin GPIO_PIN_4
#define BLE_IRQ_GPIO_Port GPIOA
#define BLE_CS_Pin GPIO_PIN_0
#define BLE_CS_GPIO_Port GPIOB
#define Battery_Pin GPIO_PIN_1
#define Battery_GPIO_Port GPIOB
#define BLE_RSTN_Pin GPIO_PIN_2
#define BLE_RSTN_GPIO_Port GPIOB
#define I2C2_SCL_Pin GPIO_PIN_10
#define I2C2_SCL_GPIO_Port GPIOB
#define LIS2MDL_CS_Pin GPIO_PIN_12
#define LIS2MDL_CS_GPIO_Port GPIOB
#define ReservedB14_Pin GPIO_PIN_14
#define ReservedB14_GPIO_Port GPIOB
#define LSM6DS33_CS_Pin GPIO_PIN_8
#define LSM6DS33_CS_GPIO_Port GPIOA
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define ReservedA15_Pin GPIO_PIN_15
#define ReservedA15_GPIO_Port GPIOA
#define I2C2_SDA_Pin GPIO_PIN_3
#define I2C2_SDA_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_4
#define LD2_GPIO_Port GPIOB
#define LD1_Pin GPIO_PIN_5
#define LD1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
