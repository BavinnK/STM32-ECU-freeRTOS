/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_gpio.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#include "MyAdc.h"
#include "MyPwm.h"
#include "MyRelay.h"
//#include "MyUsart2.h"
#include "Myhcsr04.h"
#include "stdio.h"
#include <string.h>

typedef struct {
	uint16_t raw_temp;
	uint16_t raw_throttle;
} ADCData_t;
//processed data
typedef struct {
	uint16_t temperature_c;
	uint16_t throttle_percent;
	uint16_t fuel_percent;
	FanSpeed_t fan_cmd;
} ECUData_t;
typedef struct{
	uint16_t throttle_percent;
	FanSpeed_t fan_cmd;


}ECUFANSpeed_t;
//queue to send raw ADC data to the logic task
QueueHandle_t xADCDataQueue;
QueueHandle_t xECUDataQueue;
QueueHandle_t xFanCommandQueue;
QueueHandle_t xFuelDataQueue;
SemaphoreHandle_t xHcsr04Semaphore;


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
ADC_HandleTypeDef hadc1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile uint16_t adc_buffer[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void xTaskReadADC(void *pvParameters);
void xTaskECULogic(void *pvParameters);
void xTaskFanSpeed(void *pvParameters);
void xTaskHcsr04(void *pvParameters);
void xTaskTFTdraw(void *pvParameters);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
	//ILI9341_Init();
	//adc_init();
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	//ADC DMA activated
	//MX_ADC1_Init();
	//adc_init();
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	NVIC_SetPriority(TIM1_CC_IRQn, 6);
	NVIC_EnableIRQ(TIM1_CC_IRQn);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc_buffer, 2);


//	char buff1[50];
//	sprintf(buff1, "Tasks created successfully. Starting\r\n");
//	HAL_UART_Transmit(&huart2, (uint8_t*) buff1, 52, HAL_MAX_DELAY);
	xHcsr04Semaphore = xSemaphoreCreateBinary();
	xADCDataQueue = 	xQueueCreate(1, sizeof(ADCData_t));
	xECUDataQueue = 	xQueueCreate(1, sizeof(ECUData_t));
	xFanCommandQueue=	xQueueCreate(1,sizeof(ECUFANSpeed_t));
	xFuelDataQueue = 	xQueueCreate(1,sizeof(uint16_t));

	if (xADCDataQueue == NULL || xECUDataQueue == NULL || xFanCommandQueue == NULL || xFuelDataQueue == NULL || xHcsr04Semaphore == NULL) {
		//FATAL queue creation failed
		Error_Handler();

	}
	xTaskCreate(xTaskReadADC, "ADCdata", 1024, NULL, 4, NULL);		/* Task to read data from LM35DZ, and POT */
	xTaskCreate(xTaskECULogic, "ECU_print", 1024, NULL, 3, NULL);
	/* Task to send the data from ReadADC task,
	* basically from the producer tasks, and the logic is inside this task
	* this task decides to move data from there to there and send commands to other tasks.
	*/
	xTaskCreate(xTaskFanSpeed, "FanSpeed", 512, NULL, 4, NULL); /* Task to get the command from the ecuLogic and depending on that command turns on relays */
	xTaskCreate(xTaskHcsr04, "fuelData", 256, NULL, 2, NULL);	/* this is producer task, it produces data which is the fuel data, and sends the data by Queue to the ecuLogic */
	xTaskCreate(xTaskTFTdraw, "tftScreen", 1024, NULL, 1, NULL);/* again this is consumer Task, gets the data from the ecuLogic, and prints it on the tft */

	vTaskStartScheduler();
	// Start the ADC DMA transfer. This is fire-and-forget.

	// Create the Heartbeat task.

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1) {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 90;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_DC_Pin */
  GPIO_InitStruct.Pin = LCD_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_DC_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// ... your RTOS task functions will also go here ...
/**
 * @brief  xTaskReadADC: Periodically reads the DMA buffer and sends raw sensor data to a queue.
 */
void xTaskReadADC(void *pvParameters) {
	ADCData_t adc_data;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = pdMS_TO_TICKS(20); // Run at 50Hz

	for (;;) {
		// Wait for the next cycle.
		vTaskDelayUntil(&xLastWakeTime, xFrequency);

		// Get the latest data from the DMA buffer
		adc_data.raw_temp = adc_buffer[0];
		adc_data.raw_throttle = adc_buffer[1];

		// Send the packaged data to the ADC queue, overwriting if full.
		xQueueOverwrite(xADCDataQueue, &adc_data);
	}
}

/**
 * @brief  xTaskECULogic: (Test Stub) Waits for ADC data and prints it via UART.
 */
void xTaskECULogic(void *pvParameters) {
	ADCData_t received_adc={0};
	ECUData_t current_state_disp={0};
	ECUFANSpeed_t current_fan_state={0};
	uint16_t fuel_lvl=0;
	char buffer[100];

	for (;;) {
		// Wait forever until a message arrives in the ADC queue.
		xQueueReceive(xADCDataQueue, &received_adc, 0);
		xQueueReceive(xFuelDataQueue, &fuel_lvl, 0);


		current_state_disp.temperature_c = (received_adc.raw_temp * 81) / 1000;
		uint16_t data= (received_adc.raw_throttle * 100)/ 4095;
		current_state_disp.throttle_percent = data;
		current_fan_state.throttle_percent=data;


		if (current_state_disp.temperature_c >= 60 || current_state_disp.throttle_percent>=80) {
			current_fan_state.fan_cmd=FAN_SPEED_HIGH;
			current_state_disp.fan_cmd = FAN_SPEED_HIGH;
		}
		else if (current_state_disp.temperature_c >=40 && current_state_disp.temperature_c < 60) {
			current_fan_state.fan_cmd= FAN_SPEED_MEDIUM;
			current_state_disp.fan_cmd = FAN_SPEED_MEDIUM;
		}
		else if (current_state_disp.temperature_c >=5 && current_state_disp.temperature_c < 40) {
			current_fan_state.fan_cmd=FAN_SPEED_LOW;
			current_state_disp.fan_cmd = FAN_SPEED_LOW;
		}
		else if (current_state_disp.temperature_c < 5) {
			current_fan_state.fan_cmd=FAN_SPEED_OFF;
			current_state_disp.fan_cmd = FAN_SPEED_OFF;
		}
		xQueueSend(xECUDataQueue,&fuel_lvl,0);
		xQueueOverwrite(xFanCommandQueue,&current_fan_state);
		sprintf(buffer, "Temp: %dC | Thr: %d%% | Fan Cmd: %d\r\n",current_state_disp.temperature_c, current_state_disp.throttle_percent,current_state_disp.fan_cmd);
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer),HAL_MAX_DELAY);
		sprintf(buffer,"fuel level: %d\n\r",fuel_lvl);
		HAL_UART_Transmit(&huart2, (uint8_t *) buffer, strlen(buffer), HAL_MAX_DELAY);
		/* run this task 10 times per second */
		vTaskDelay(pdMS_TO_TICKS(100));

	}
}
void xTaskFanSpeed(void *pvParameters){
	ECUFANSpeed_t received_ecu_data;

	for(;;){
		if(xQueueReceive(xFanCommandQueue, &received_ecu_data, portMAX_DELAY)==pdPASS){
			relay_set_fan_speed(received_ecu_data.fan_cmd);
			}
		}
	}

void xTaskHcsr04(void *pvParameters){
	const uint8_t fuel_full_cm=5;
	const uint8_t fuel_empty_cm=20;

	while(1){

		hcsr04_trig_hc();

		//we will wait for the ISR to send data back when we triggered the hcsr04
		if(xSemaphoreTake(xHcsr04Semaphore, pdMS_TO_TICKS(200)) == pdTRUE){


			uint32_t distance_cm=hcsr04_get_pulse_width()/58;
			uint16_t fuel_perc=0;
			if(distance_cm<=fuel_full_cm){
				fuel_perc=100;
			}
			else if(distance_cm>=fuel_empty_cm){
				fuel_perc=0;
			}
			else{
				//interpolation equation
				fuel_perc=100-(((distance_cm-fuel_full_cm)*100)/(fuel_empty_cm-fuel_full_cm));
			}
			xQueueSend(xFuelDataQueue,&fuel_perc,0);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));//we run this task every 1000 ms
	}

}
void xTaskTFTdraw(void *pvParameters){
	ECUData_t recived_data={0};
	char buffer[100];
	char buffer1[30];
	sprintf(buffer1,"BAVREX Industry");
	while(1){
	xQueueReceive(xECUDataQueue, &recived_data, 0);


	sprintf(buffer,"Oil Temperature: %d\n\r Fan Speed: %d\n\r RPM: %d\n\r Fuel Level: %d",
			recived_data.temperature_c,
			recived_data.fan_cmd,
			recived_data.throttle_percent,
			recived_data.fuel_percent);
	ILI9341_Draw_Text(buffer, 10, 10, GREEN, 20, BLACK);
	}

}
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
	while (1) {
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
