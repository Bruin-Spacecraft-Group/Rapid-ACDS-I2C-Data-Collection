/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BMX160_ADDR 0x68<<1 // PULL ADR HIGH
#define BMX160_ACCEL_X 0x12
#define BMX160_ACCEL_Y 0x14
#define BMX160_ACCEL_Z 0x16
#define BMX160_MAG_X 0x04
#define BMX160_MAG_Y 0x06
#define BMX160_MAG_Z 0x08
#define BMX160_GYRO_X 0x0c
#define BMX160_GYRO_Y 0x0e
#define BMX160_GYRO_Z 0x10
#define MAGN_IF_0 0x4C
#define MAGN_IF_1 0x4D
#define MAGN_IF_2 0x4E
#define MAGN_IF_3 0x4F
#define MAGN_CONFIG 0x44
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void UART_PRINT_VAL(double value);
void UART_PRINT_TEXT(uint8_t* MSG);

void BMX160_INIT(void);
double BMX160_GET_DATA(uint8_t addr, uint16_t dataSize);
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
    double xAccel = 0;
    double yAccel = 0;
    double zAccel = 0;
    double xMag = 0;
    double yMag = 0;
    double zMag = 0;
    double xGyro = 0;
    double yGyro = 0;
    double zGyro = 0;


    HAL_Delay(500);
    BMX160_INIT();
    HAL_Delay(500);
    BMX160_INIT();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



	  /*uint8_t receiveData;
	  HAL_I2C_Mem_Read(&hi2c1, BMX160_ADDR, 0x02, 1, &receiveData, 1, 100);
	  UART_PRINT_VAL(receiveData);*/


	  xAccel = BMX160_GET_DATA(BMX160_ACCEL_X, 2);
	  HAL_Delay(1);
	  /*
	  yAccel = BMX160_GET_DATA(BMX160_ACCEL_Y, 2);
	  HAL_Delay(1);
	  zAccel = BMX160_GET_DATA(BMX160_ACCEL_Z, 2);
	  HAL_Delay(3);

	  xMag = BMX160_GET_DATA(BMX160_MAG_X, 2);
	  HAL_Delay(1);

	  /*uint8_t receivedData;
	  HAL_I2C_Mem_Read(&hi2c1, BMX160_ADDR, 0x1B, 1, &receivedData, 1, 100);
	  UART_PRINT_VAL(receivedData);*/
/*
	  yMag = BMX160_GET_DATA(BMX160_MAG_Y, 2);
	  HAL_Delay(1);
	  zMag = BMX160_GET_DATA(BMX160_MAG_Z, 2);
	  HAL_Delay(3);

	  xGyro = BMX160_GET_DATA(BMX160_GYRO_X, 2);
	  HAL_Delay(1);
	  yGyro = BMX160_GET_DATA(BMX160_GYRO_Y, 2);
	  HAL_Delay(1);
	  zGyro = BMX160_GET_DATA(BMX160_GYRO_Z, 2);
	  HAL_Delay(3);
	  */

      UART_PRINT_TEXT("Accelerometer: ");
	  UART_PRINT_TEXT("( ");
	  UART_PRINT_VAL(xAccel);
	  /*
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(yAccel);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(zAccel);
	  */
	  UART_PRINT_TEXT(" )\n");
/*
	  UART_PRINT_TEXT("Magnetometer: ");
	  UART_PRINT_TEXT("( ");
	  UART_PRINT_VAL(xMag);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(yMag);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(zMag);
	  UART_PRINT_TEXT(" )\n");

	  UART_PRINT_TEXT("Gyro: ");
	  UART_PRINT_TEXT("( ");
	  UART_PRINT_VAL(xGyro);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(yGyro);
	  UART_PRINT_TEXT(", ");
	  UART_PRINT_VAL(zGyro);
	  UART_PRINT_TEXT(" )\n");
*/
	  HAL_Delay(100);
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
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
  hi2c1.Init.Timing = 0x30A0A7FB;
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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void UART_PRINT_VAL(double value){
	char total[50];
	char temp[10];
	if(value < 0){
	   UART_PRINT_TEXT("-");
	}
	sprintf(total, "%i", abs((int)value));
	strcat(total, ".");
	double currentVal = (value - (int) value);
	for(int a=0;a<6;a++){
		currentVal *= 10;
		sprintf(temp, "%i", abs((int)currentVal));
		strcat(total, temp);
		currentVal -= (int)currentVal;
	}
	HAL_UART_Transmit(&huart2, total, strlen(total), 100);
}


void UART_PRINT_TEXT(uint8_t* MSG){
	HAL_UART_Transmit(&huart2, MSG, strlen(MSG), 100);
}

void BMX160_INIT(void){
	uint8_t softreset[1] = {0xB6};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x7e, 1, softreset, 1, HAL_MAX_DELAY); //soft reset
	uint8_t gyrorange[1] = {0x04};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x43, 1, gyrorange, 1, 100); //set GYR_RANGE to be full precision (+/- 125 deg/s)
	uint8_t stepconfig1[1] = {0x15};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x7a, 1, stepconfig1, 1, 100); //set step config to normal mode
	uint8_t stepconfig2[1] = {0x03};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x7b, 1, stepconfig2, 1, 100); //set step config to normal mode
	uint8_t accelpmu[1] = {0x11};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x7e, 1, accelpmu, 1, 100); //set accelerometer pmu mode to normal
	HAL_Delay(50);
	uint8_t gyropmu[1] = {0x15};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x7e, 1, gyropmu, 1, 100); //set gyro pmu mode to normal
	HAL_Delay(100);

	uint8_t magpmu[1] = {0x19};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x7e, 1, magpmu, 1, 100); //set magnetometer pmu mode to normal
	HAL_Delay(10);

	uint8_t magbuffer[12] = {0x80 /*first setting*/,0x01,0x4B /*sleep mode*/,0x04, 0x51 /*preset xy*/, 0x0E,0x52, /*preset z*/0x02,0x4C,0x42,0x08 /*config*/,0x03};//0x4C,0x42,0x08,0x03};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_0, 1, &magbuffer[0], 1, 100);
	HAL_Delay(50);

	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_3, 1, &magbuffer[1], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_2, 1, &magbuffer[2], 1, 100);

	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_3, 1, &magbuffer[3], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_2, 1, &magbuffer[4], 1, 100);

	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_3, 1, &magbuffer[5], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_2, 1, &magbuffer[6], 1, 100);

	HAL_I2C_Mem_Write(&hi2c1,BMX160_ADDR, MAGN_IF_3, 1, &magbuffer[7], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_2, 1, &magbuffer[8], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_1, 1, &magbuffer[9], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_CONFIG, 1, &magbuffer[10], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, MAGN_IF_0, 1, &magbuffer[11], 1, 100);
	HAL_Delay(50);


/*
	uint8_t accelconfig[1] = {0x2B};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x40, 1, accelconfig, 1, HAL_MAX_DELAY); // set accel_config to us = 0b0, pw = 0b010, and odr = 0b1011/800 Hz
	uint8_t accelrange[1] = {0x3};
	HAL_I2C_Mem_Write(&hi2c1, BMX160_ADDR, 0x41, 1, accelrange, 1, HAL_MAX_DELAY); // set accel_range to +/- 2g*/

}


double BMX160_GET_DATA(uint8_t addr, uint16_t dataSize){
	double val = 0;
	uint16_t value = 0;
	uint8_t receiveData[dataSize];
	HAL_I2C_Mem_Read(&hi2c1, BMX160_ADDR, addr, 1, receiveData, dataSize, 100);
	value = (receiveData[1] << 8 | receiveData[0]);
	if(value > 0x7fff){
		value = ~value;
		val = -value;
	}
	else{
		val = value;
	}

	val *= 0.000061035; // (1/(2^15)) to get g

	return val;
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
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
