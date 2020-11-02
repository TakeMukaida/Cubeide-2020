/*
 * memo.c
 *
 *  Created on: Jul 16, 2020
 *      Author: Takeki Mukaida
 */
/*//date:R20716
 char msg[] = "Hello STM32\r\n";
 char msg2[] = "Push Button\r\n";
 char rec1[] = "Recieve1\r\n";
 char rec2[] = "Recieve2\r\n";
 char nonans[] = "Error\r\n";

 char rev;

 HAL_UART_Transmit(&huart2, (uint8_t *)msg, sizeof(msg), 3000);

 if(HAL_UART_Receive(&huart2, &rev, 1, 1000) == HAL_OK) {
		  switch(rev) {
		  case '1':
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			  HAL_UART_Transmit(&huart2, (uint8_t *)rec1, sizeof(rec1), 3000);
			  break;
		  case '2':
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			  HAL_UART_Transmit(&huart2, (uint8_t *)rec2, sizeof(rec2), 3000);
			  break;
		  default:
			  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			  HAL_UART_Transmit(&huart2, (uint8_t *)nonans, sizeof(nonans), 3000);
			  break;
		  }
	  }
 */



