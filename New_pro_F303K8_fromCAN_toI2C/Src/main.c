/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char scount[100];

char powers = 0;

//CAN
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;

uint8_t               TxData[8] = {0};
uint8_t               RxData[8] = {0};
uint32_t              TxMailbox;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) { //Receive callback function
	uint8_t Data[4];

  	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, Data) != HAL_OK) {
    		Error_Handler();
  	}
  	else {
  		for(int i = 0; i < 4; i++)
  			RxData[i] = Data[i];
  	}

  	for(int i = 0; i < 4; i++) {
		sprintf(scount, "%d:%05d,", i, (int)RxData[i]);
		HAL_UART_Transmit(&huart1, scount, strlen(scount) + 1, 3000);
		HAL_UART_Transmit(&huart2, scount, strlen(scount) + 1, 3000);
	}
	sprintf(scount, "\r\n");
	HAL_UART_Transmit(&huart1, scount, strlen(scount) + 1, 3000);
	HAL_UART_Transmit(&huart2, scount, strlen(scount) + 1, 3000);

  	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	//Reception start command function
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  MX_I2C1_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  MX_GPIO_Init();
    HAL_CAN_Start(&hcan);
	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
		Error_Handler();
	}
	/*
	char rxbuf[1];
	char txbuf1[] = "'A' pressed\r\n";
	char txbuf2[] = "'B' Pressed\r\n";
	char txbuf3[] = "Other Pressed\r\n";
	*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
		Error_Handler();
	}

//	if(1) {
		powers = (signed char)30;

		if(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_A, &powers, 1, 1000) != HAL_OK) {
			sprintf(scount, "error");
			HAL_UART_Transmit(&huart1, scount, strlen(scount) + 1, 3000);
			HAL_UART_Transmit(&huart2, scount, strlen(scount) + 1, 3000);;
		}

		powers = (signed char)-30;	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_B, &powers, 1, 1000);
		powers = (signed char)RxData[2];	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_C, &powers, 1, 1000);
		powers = (signed char)RxData[3];	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)B_ADDR,   &powers, 1, 1000);

/*
		if((fabs(target_x - vector_x) > 0.5) || (fabs(target_y - vector_y) > 0.5)) {
			powers = (signed char)tire[0];	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_A, &powers, 1, 1000);
			powers = (signed char)tire[2];	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_B, &powers, 1, 1000);
			powers = (signed char)tire[1];	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_C, &powers, 1, 1000);
		}
*/

//	}
/*	else {
		powers = 0;	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_A, &powers, 1, 1000);
		powers = 0;	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_B, &powers, 1, 1000);
		powers = 0;	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)M_ADDR_C, &powers, 1, 1000);
		powers = 0;	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)B_ADDR,   &powers, 1, 1000);
	}

	sprintf(scount, "test");
	HAL_UART_Transmit(&huart1, scount, strlen(scount) + 1, 3000);
	HAL_UART_Transmit(&huart2, scount, strlen(scount) + 1, 3000);*/
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL15;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 6;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_4TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
	/*
	uint32_t fId1   =  0x350 << 5;        // フィルターID1
	uint32_t fMask1 = (0x3F0 << 5) | 0x8; // フィルターマスク1
	uint32_t fId2   =  0x400 << 5;        // フィルターID2
	uint32_t fMask2 = (0x700 << 5) | 0x8; // フィルターマスク2

	filter.FilterIdHigh         = fId1;                  // フィルターID1
	filter.FilterIdLow          = fId2;                  // フィルターID2
	filter.FilterMaskIdHigh     = fMask1;                // フィルターマスク1
	filter.FilterMaskIdLow      = fMask2;                // フィルターマスク2
	*/
  	CAN_FilterTypeDef  filter;
	filter.FilterIdHigh         = 0;                        // フィルターID(上位16ビット)
	filter.FilterIdLow          = 0;                        // フィルターID(下位16ビット)
	filter.FilterMaskIdHigh     = 0;                        // フィルターマスク(上位16ビット)
	filter.FilterMaskIdLow      = 0;                        // フィルターマスク(下位16ビット)
	filter.FilterScale          = CAN_FILTERSCALE_32BIT;    // フィルタースケール
	filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;         // フィルターに割り当てるFIFO
	filter.FilterBank           = 0;                        // フィルターバンクNo
	filter.FilterMode           = CAN_FILTERMODE_IDMASK;    // フィルターモード
	filter.SlaveStartFilterBank = 14;                       // スレーブCANの開始フィルターバンクNo
	filter.FilterActivation     = ENABLE;                   // フィルター無効／有効
	/*
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh = 0x456<<5;
	sFilterConfig.FilterIdLow = 0x456<<5;
	sFilterConfig.FilterMaskIdHigh = 0x456<<5;
	sFilterConfig.FilterMaskIdLow = 0x456<<5;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;
	 */
	if (HAL_CAN_ConfigFilter(&hcan, &filter) != HAL_OK)
	{
	  Error_Handler();
	}
  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 921600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 921600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */




//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {	//TWelite
//	HAL_UART_Receive_IT(&huart1, &RxData, RECEIVE_BYTE);
//	HAL_UART_Receive_IT(&huart2, &RxData, RECEIVE_BYTE);
	//HAL_UART_Receive(&huart3,(uint8_t *)RxData, sizeof(RxData), 0xF);

	//for(int i = 0; i < RECEIVE_BYTE; i++)		//data_change
	//	CkData[i] = RxData[i];
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
