/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stdio.h"
#include "string.h"
#include "math.h"

#include "includes.h"

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
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef);
void omni3(double, double, double);
void pid_control_x(double, double, double*, int);
void pid_control_y(double, double, double* ,int);
void pid_control_theta(double, double, double*, int);
int16_t read_encoder_value1();
int16_t read_encoder_value2();
int16_t read_encoder_value3();
void print5(uint16_t);

void sequence(short, short, double *, double *);
void sequence_Li(short, double *, double *);	//Robot01_Lithium
void sequence_Na(short, double *, double *);	//Robot02_Natrium
void sequence_K (short, double *, double *);	//Robot03_Kalium
void sequence_Sr(short, double *, double *);	//Robot04_Strontium
void sequence_Ba(short, double *, double *);	//Robot05_Barium
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA

#define BIAS (30)
#define L_C  (-(100 - BIAS))
#define L_B  (-(175 - BIAS))
#define L_A  (-(250 - BIAS))
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
