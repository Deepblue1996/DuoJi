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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "string.h"
#include "malloc.h"
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

/* USER CODE BEGIN PV */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
char *sendResponse(char *msg, char *isOk);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */


    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_TIM2_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        // 200/20=10 200-x=y y*10=ms
        // 1000/20 = 50/ms
        // 0.5ms  = 25  ----------------正向最大转速
        // 1.5ms  = 75  ----------------速度为0
        // 2.5ms  = 125 ----------------反向最大转速

        char *string = sendResponse("AT+GMR\r\n", "OK");

        HAL_Delay(1000);

        //responseData(&huart1, rxs);
        //sendData(&huart1, msg);

//        HAL_UART_Receive(&huart1, (uint8_t *) rxBuffer2, strlen(rxBuffer2), 1000);

        //HAL_UART_Receive_IT(&huart1, (uint8_t *) rxBuffer2, 100);
        //HAL_UART_Receive_IT(&huart2, (uint8_t *) rxBuffer, 100);

/*        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//
//        // 暂停
        // 1000 100%
        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 125);
//
        HAL_Delay(200);

        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 75);
//
        HAL_Delay(200);

        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 25);
//
        HAL_Delay(200);*/

//        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 400);
//
//        HAL_Delay(600);
//
//        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 1000);
//
//        HAL_Delay(600);
//
//        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 800);
//
//        HAL_Delay(600);
//
//        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 200);
//
//        HAL_Delay(600);
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
char *sendResponse(char *msg, char *isOk) {

    int index = 5;

    char rxBuffer[255];

    while (index > 0) {
        HAL_UART_Transmit(&huart1, (uint8_t *) msg, strlen(msg), 1);
        /*Receive command and save in "rxBuffer" array with 5s timeout*/
        HAL_UART_Receive(&huart1, (uint8_t *) rxBuffer, sizeof(rxBuffer), 5000);
        /*Process recived command*/
        if (strstr(rxBuffer, isOk) != 0) {
            char *str = strstr(rxBuffer, "\000");
            char *dest = malloc(strlen(str));
            memset(dest, 0, strlen(dest));
            strncpy(dest, str + strlen(msg), strlen(str) - strlen(msg));
            char len = strlen(dest);
            dest[len - 1] = '\0';
            return dest;
        }
        index--;
    }
    return "ERROR";
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    UNUSED(huart);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
/* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    // 1ms
    if (htim->Instance == htim2.Instance) {

        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
        }

    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
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
