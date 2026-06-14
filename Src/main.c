/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "network.h"     
#include "network_data.h"
#include "network_data_params.h"

char rx_buf[50];

// ????,??????????? 96 ??
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__ARMCC_VERSION)
__align(4) float ai_input_data[4];
__align(4) float ai_output_data[3];
__align(4) uint8_t activations[96]; // <--- ??? 96
#else
float ai_input_data[4] __attribute__((aligned(4)));
float ai_output_data[3] __attribute__((aligned(4)));
uint8_t activations[96] __attribute__((aligned(4))); // <--- ??? 96
#endif

ai_handle network = AI_HANDLE_NULL;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
void AI_Init(void)
{
  // 1. ???? CRC 
  __HAL_RCC_CRC_CLK_ENABLE();

  ai_error err;

  // 2. ??????
  err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE)
  {
    printf("AI CREATE FAIL! TYPE: %d, CODE: %d\r\n", err.type, err.code);
    return;
  }

  // 3. ???????
  ai_network_params params;
  
  // 4. ?????????????????
  if (ai_network_data_params_get(&params) != true)
  {
     err = ai_network_get_error(network);
     printf("GET PARAMS FAIL! TYPE: %d, CODE: %d\r\n", err.type, err.code);
     return;
  }

  // 5. ???????????????????? activations ??
  // ???????:params ????? map_activations ????
  AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, 0, activations);

  // 6. ????????????
  if (!ai_network_init(network, &params))
  {
    err = ai_network_get_error(network);
    printf("AI INIT FAIL! TYPE: %d, CODE: %d\r\n", err.type, err.code);
    return;
  }

  printf("AI INIT ALL SUCCESS !!!\r\n");
}
int AI_Run(float *in, float *out)
{
  // 1. ????????????,??????????????? buffer ??
  ai_buffer* ai_input_ptr  = ai_network_inputs_get(network, NULL);
  ai_buffer* ai_output_ptr = ai_network_outputs_get(network, NULL);

  if (ai_input_ptr != NULL && ai_output_ptr != NULL)
  {
    // 2. ??????????????????????
    ai_input_ptr[0].data  = AI_HANDLE_PTR(in);
    ai_output_ptr[0].data = AI_HANDLE_PTR(out);
  }
  else
  {
    printf("Error: Cannot get official AI buffers!\r\n");
    return 0;
  }

  // 3. ??????
  ai_network_run(network, ai_input_ptr, ai_output_ptr);

  // 4. ???????????
  int max_idx = 0;
  for(int i = 1; i < 3; i++)
  {
    if(out[i] > out[max_idx]) 
    {
      max_idx = i;
    }
  }
  return max_idx;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
AI_Init();
printf("Iris Ready\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t ch;
  int rx_index = 0;
  memset(rx_buf, 0, sizeof(rx_buf));
  while (1)
  {
		
		if (HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY) == HAL_OK)
    {
      // ???????,????????,????
      if (ch == '\n' || ch == '\r')
      {
        if (rx_index > 0) // ?????????
        {
          rx_buf[rx_index] = '\0'; // ?????????

          // ???? AI ??
          if(sscanf(rx_buf, "%f,%f,%f,%f",
                    &ai_input_data[0],
                    &ai_input_data[1],
                    &ai_input_data[2],
                    &ai_input_data[3]) == 4)
          {
						printf(">> sscanf OK! Data: %.2f, %.2f\r\n", ai_input_data[0], ai_input_data[1]);
            int max_index = AI_Run(ai_input_data, ai_output_data);
						printf("Raw Output: [%.4f, %.4f, %.4f]\r\n", ai_output_data[0], ai_output_data[1], ai_output_data[2]);

            switch(max_index){
              case 0: printf("Setosa\r\n"); break;
              case 1: printf("Versicolor\r\n"); break;
              case 2: printf("Virginica\r\n"); break;
            }
          }
          
          // ????,????????,????
          rx_index = 0;
          memset(rx_buf, 0, sizeof(rx_buf));
        }
      }
      else
      {
        // ??????,??????????,?????????
        if (rx_index < sizeof(rx_buf) - 1)
        {
          rx_buf[rx_index++] = ch;
        }
        else
        {
          // ??????????????
          rx_index = 0;
          memset(rx_buf, 0, sizeof(rx_buf));
        }
      }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
