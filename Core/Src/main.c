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

//#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_gpio.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
//#include "MyAdc.h"
#include "MyPwm.h"
#include "MyRelay.h"
#include "MyAdcDMA.h"
#include "MyUsart.h"
#include "clock.h"
#include "MySPI.h"
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
} ECUData_T1;
typedef struct {
	uint16_t throttle_percent;
	FanSpeed_t fan_cmd;

} ECUFANSpeed_t;
//queue to send raw ADC data to the logic task
QueueHandle_t xADCDataQueue;
QueueHandle_t xECUDataQueue;
QueueHandle_t xFanCommandQueue;
QueueHandle_t xFuelDataQueue;
SemaphoreHandle_t xHcsr04Semaphore;
SemaphoreHandle_t xSPIMutex;

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
volatile uint16_t adc_buffer[2];
/* USER CODE END PV */
void SystemClock_Config(void);
/* Private function prototypes -----------------------------------------------*/

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
  //SystemClock_Config();
	systemClock_180MHz();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
	SPIx_init(SPI1,GPIOB, 1, GPIOB, 15, GPIOB, 14, 20, MSB);
	relay_init();
	hcsr04_init();
	//systemClock_180MHz();
	adc_config_t adc_config;
	adc_config.channel[0]=ADCx_CHANNEL_0;
	adc_config.channel[1]=ADCx_CHANNEL_1;
	adc_config.sample_time=480;

	DMA_config_t dma_config;
	dma_config.CHANNEL=0;
	dma_config.DIRECTION=PER_TO_MEM;
	dma_config.DMA_STREAM=DMA2_Stream0;
	dma_config.LENGTH=2;
	dma_config.MEMORY_ADDR=(uint32_t*)&adc_buffer;
	dma_config.MEMORY_DATA_SIZE=MEM_HALF_WORD;
	dma_config.MODE=CIRCULAR;
	dma_config.PERIPHERAL_ADDR=(uint32_t*)&ADC1->DR;
	dma_config.PERIPHERAL_DATA_SIZE=PER_HALF_WORD;
	dma_config.PRIORITY=PRIOTITY_MED;
	adc_dma_init(ADC1, &adc_config, DMA2, &dma_config, 2);
	Usart2_init(9600);
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	NVIC_SetPriority(TIM1_CC_IRQn, 5);
	NVIC_EnableIRQ(TIM1_CC_IRQn);
	NVIC_SetPriority(USART2_IRQn,6);
	NVIC_EnableIRQ(USART2_IRQn);


	//char buff1[50];
	//sprintf(buff1, "Tasks created successfully. Starting\r\n");
	//HAL_UART_Transmit(&huart2, (uint8_t*) buff1, 52, HAL_MAX_DELAY);
	xHcsr04Semaphore = xSemaphoreCreateBinary();
	xSPIMutex = xSemaphoreCreateMutex();
	xADCDataQueue = xQueueCreate(1, sizeof(ADCData_t));
	xECUDataQueue = xQueueCreate(1, sizeof(ECUData_T1));
	xFanCommandQueue = xQueueCreate(1, sizeof(ECUFANSpeed_t));
	xFuelDataQueue = xQueueCreate(1, sizeof(uint16_t));

	if (xADCDataQueue == NULL || xECUDataQueue == NULL
			|| xFanCommandQueue == NULL || xFuelDataQueue == NULL
			|| xHcsr04Semaphore == NULL) {
		//FATAL queue creation failed
		Error_Handler();

	}
	xTaskCreate(xTaskReadADC, "ADCdata", 1024, NULL, 4, NULL); /* Task to read data from LM35DZ, and POT */
	xTaskCreate(xTaskECULogic, "ECU_print", 1024, NULL, 3, NULL);

	/* Task to send the data from ReadADC task,
	 * basically from the producer tasks, and the logic is inside this task
	 * this task decides to move data from there to there and send commands to other tasks.
	 */
	xTaskCreate(xTaskFanSpeed, "FanSpeed", 512, NULL, 4, NULL); /* Task to get the command from the ecuLogic and depending on that command turns on relays */
	xTaskCreate(xTaskHcsr04, "fuelData", 256, NULL, 2, NULL); /* this is producer task, it produces data which is the fuel data, and sends the data by Queue to the ecuLogic */
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

void xTaskReadADC(void *pvParameters) {
	ADCData_t adc_data;
	TickType_t xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = pdMS_TO_TICKS(20); // Run at 50Hz

	for (;;) {
		//wee will wait for the next cycle
		vTaskDelayUntil(&xLastWakeTime, xFrequency);

		//getting the latest data from the DMA buffer
		adc_data.raw_temp = adc_buffer[0];
		adc_data.raw_throttle = adc_buffer[1];

		//sending the packaged data to the ADC queue, overwriting if full.
		xQueueOverwrite(xADCDataQueue, &adc_data);
	}
}

void xTaskECULogic(void *pvParameters) {
	ADCData_t received_adc = { 0 };
	ECUData_T1 current_state_disp = { 0 };
	ECUFANSpeed_t current_fan_state = { 0 };
	uint16_t fuel_lvl = 0;


	for (;;) {
		// waitin forever until a message arrives in the ADC queue.
		xQueueReceive(xADCDataQueue, &received_adc, 0);
		xQueueReceive(xFuelDataQueue, &fuel_lvl, 0);
		uint16_t inverted_raw = 4095 - received_adc.raw_temp;
		current_state_disp.temperature_c = (inverted_raw * 81) / 1000;
		//current_state_disp.temperature_c = (received_adc.raw_temp * 81) / 1000;
		uint16_t data = (received_adc.raw_throttle * 100) / 4095;
		current_state_disp.throttle_percent = data;
		current_fan_state.throttle_percent = data;
		current_state_disp.fuel_percent=fuel_lvl;

		if (current_state_disp.temperature_c >= 60
				|| current_state_disp.throttle_percent >= 80) {
			current_fan_state.fan_cmd = FAN_SPEED_HIGH;
			current_state_disp.fan_cmd = FAN_SPEED_HIGH;
		} else if (current_state_disp.temperature_c >= 40
				&& current_state_disp.temperature_c < 60) {
			current_fan_state.fan_cmd = FAN_SPEED_MEDIUM;
			current_state_disp.fan_cmd = FAN_SPEED_MEDIUM;
		} else if (current_state_disp.temperature_c >= 5
				&& current_state_disp.temperature_c < 40) {
			current_fan_state.fan_cmd = FAN_SPEED_LOW;
			current_state_disp.fan_cmd = FAN_SPEED_LOW;
		} else if (current_state_disp.temperature_c < 5) {
			current_fan_state.fan_cmd = FAN_SPEED_OFF;
			current_state_disp.fan_cmd = FAN_SPEED_OFF;
		}


		printf("Temp: %dC | Thr: %d%% | Fan Cmd: %d fuel level: %d\n\r",
						current_state_disp.temperature_c,
						current_state_disp.throttle_percent, current_state_disp.fan_cmd,
						current_state_disp.fuel_percent);


		xQueueOverwrite(xECUDataQueue, &fuel_lvl);
		xQueueOverwrite(xFanCommandQueue, &current_fan_state);
		/* run this task 10 times per second */
		vTaskDelay(pdMS_TO_TICKS(100));

	}
}
void xTaskFanSpeed(void *pvParameters) {
	ECUFANSpeed_t received_ecu_data;

	for (;;) {
		if (xQueueReceive(xFanCommandQueue, &received_ecu_data,
				portMAX_DELAY)==pdPASS) {
			relay_set_fan_speed(received_ecu_data.fan_cmd);
		}
	}
}

void xTaskHcsr04(void *pvParameters) {
	const uint8_t fuel_full_cm = 5;
	const uint8_t fuel_empty_cm = 20;

	while (1) {

		hcsr04_trig_hc();

		//we will wait for the ISR to send data back when we triggered the hcsr04
		if (xSemaphoreTake(xHcsr04Semaphore, pdMS_TO_TICKS(200)) == pdTRUE) {

			uint32_t distance_cm = hcsr04_get_pulse_width() / 58;
			uint16_t fuel_perc = 0;
			if (distance_cm <= fuel_full_cm) {
				fuel_perc = 100;
			} else if (distance_cm >= fuel_empty_cm) {
				fuel_perc = 0;
			} else {
				//interpolation equation
				fuel_perc = 100
						- (((distance_cm - fuel_full_cm) * 100)
								/ (fuel_empty_cm - fuel_full_cm));
			}
			xQueueSend(xFuelDataQueue, &fuel_perc, 0);
		}
		vTaskDelay(pdMS_TO_TICKS(1000)); //we run this task every 1000 ms
	}

}

void xTaskTFTdraw(void *pvParameters) {
	ECUData_T1 recived_data = { 0 };

	//ILI9341_Init();
	if (xSemaphoreTake(xSPIMutex,portMAX_DELAY) == pdTRUE) {
		ILI9341_Init();

		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Fill_Screen(BLACK); //clear screen
		ILI9341_Draw_Text("BAVREX ENGINEERING", 40, 100, BLUE, 2, BLACK);

		ILI9341_Draw_Text("ECU Online", 90, 130, GREEN, 2, BLACK);
		xSemaphoreGive(xSPIMutex);
	}
	vTaskDelay(2500); //2.5 sec delay

	for (;;) {
		if (xQueueReceive(xECUDataQueue, &recived_data,
				pdMS_TO_TICKS(50))==pdTRUE) {
			char buff[60];
			if (xSemaphoreTake(xSPIMutex,portMAX_DELAY) == pdTRUE) {
				ILI9341_Fill_Screen(BLACK); //clear the screen
				sprintf(buff, "Oil Temp: %dC", recived_data.fan_cmd);
				ILI9341_Draw_Text(buff, 10, 50, WHITE, 2, BLACK);

				//we have the throttle in percent but we need it in RPM
				int rpm = 800 + (recived_data.throttle_percent * 62);
				sprintf(buff, "RPM: %d", rpm);
				ILI9341_Draw_Text(buff, 10, 80, WHITE, 2, BLACK);

				sprintf(buff, "Fuel Percent: %d", recived_data.temperature_c);
				ILI9341_Draw_Text(buff, 10, 110, WHITE, 2, BLACK);

				sprintf(buff, "Fan State: %d", recived_data.fuel_percent);
				ILI9341_Draw_Text(buff, 10, 140, WHITE, 2, BLACK);

				//now when we are done with the screen, we hand over the mutex for other tasks, but since no other task uses it its not neccesary
				//but its a good practice todo and use mutex
				vTaskDelay(pdMS_TO_TICKS(1000));
				xSemaphoreGive(xSPIMutex);
			}

		}
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
