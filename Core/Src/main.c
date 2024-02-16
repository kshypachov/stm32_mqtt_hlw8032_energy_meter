/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "cmsis_os.h"
#include "mbedtls.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "queue.h"
#include "HLW8032.h"
#include "SPI_flash_io.h"
#include "SPI_flash.h"
#include "spi_fs.h"
#include "lfs.h"
#include "lfs_config.h"

#include "ll_SPI_enh_abstractions.h"
#include "w5500.h"
#include "dhcp.h"
#include "socket.h"
#include "httpServer.h"
#include "httpUtil.h"
#include "ethernet_init.h"
#include "dns_service.h"
#include "http_app.h"
#include "dns_service.h"
#include "mqtt_gen_strings.h"
#include "mqtt_app.h"

#include "data_types.h"
#include "web_pages.h"
#include "md5.h"

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
CRC_HandleTypeDef hcrc;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SensorsTask */
osThreadId_t SensorsTaskHandle;
const osThreadAttr_t SensorsTask_attributes = {
  .name = "SensorsTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for RW_Settings_Tas */
osThreadId_t RW_Settings_TasHandle;
const osThreadAttr_t RW_Settings_Tas_attributes = {
  .name = "RW_Settings_Tas",
  .stack_size = 900 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for oneSecondTickTa */
osThreadId_t oneSecondTickTaHandle;
const osThreadAttr_t oneSecondTickTa_attributes = {
  .name = "oneSecondTickTa",
  .stack_size = 200 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for maintEthTask */
osThreadId_t maintEthTaskHandle;
const osThreadAttr_t maintEthTask_attributes = {
  .name = "maintEthTask",
  .stack_size = 2000 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for DebugMemUsageT */
osThreadId_t DebugMemUsageTHandle;
const osThreadAttr_t DebugMemUsageT_attributes = {
  .name = "DebugMemUsageT",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for httpServTask */
osThreadId_t httpServTaskHandle;
const osThreadAttr_t httpServTask_attributes = {
  .name = "httpServTask",
  .stack_size = 2000 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for mqttClientTask */
osThreadId_t mqttClientTaskHandle;
const osThreadAttr_t mqttClientTask_attributes = {
  .name = "mqttClientTask",
  .stack_size = 1000 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for resetWatchDog */
osThreadId_t resetWatchDogHandle;
const osThreadAttr_t resetWatchDog_attributes = {
  .name = "resetWatchDog",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SendBroadcast */
osThreadId_t SendBroadcastHandle;
const osThreadAttr_t SendBroadcast_attributes = {
  .name = "SendBroadcast",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for rowPowerSensorQ */
osMessageQueueId_t rowPowerSensorQHandle;
const osMessageQueueAttr_t rowPowerSensorQ_attributes = {
  .name = "rowPowerSensorQ"
};
/* Definitions for EthernetInfoQ */
osMessageQueueId_t EthernetInfoQHandle;
const osMessageQueueAttr_t EthernetInfoQ_attributes = {
  .name = "EthernetInfoQ"
};
/* Definitions for PowerDataQ */
osMessageQueueId_t PowerDataQHandle;
const osMessageQueueAttr_t PowerDataQ_attributes = {
  .name = "PowerDataQ"
};
/* Definitions for Curr_sensor_settings */
osMessageQueueId_t Curr_sensor_settingsHandle;
const osMessageQueueAttr_t Curr_sensor_settings_attributes = {
  .name = "Curr_sensor_settings"
};
/* Definitions for mqttQ */
osMessageQueueId_t mqttQHandle;
const osMessageQueueAttr_t mqttQ_attributes = {
  .name = "mqttQ"
};
/* Definitions for mb_tcp_settingsQ */
osMessageQueueId_t mb_tcp_settingsQHandle;
const osMessageQueueAttr_t mb_tcp_settingsQ_attributes = {
  .name = "mb_tcp_settingsQ"
};
/* Definitions for uptimeQ */
osMessageQueueId_t uptimeQHandle;
const osMessageQueueAttr_t uptimeQ_attributes = {
  .name = "uptimeQ"
};
/* Definitions for Network */
osMutexId_t NetworkHandle;
const osMutexAttr_t Network_attributes = {
  .name = "Network"
};
/* Definitions for LFS */
osMutexId_t LFSHandle;
const osMutexAttr_t LFS_attributes = {
  .name = "LFS"
};
/* Definitions for Socket */
osMutexId_t SocketHandle;
const osMutexAttr_t Socket_attributes = {
  .name = "Socket"
};
/* Definitions for ServiceSocket */
osMutexId_t ServiceSocketHandle;
const osMutexAttr_t ServiceSocket_attributes = {
  .name = "ServiceSocket"
};
/* USER CODE BEGIN PV */
/* Define buffer for UART communication with power sensor via interrupt */
uint8_t data_bufer[30];
float	test_kWh_from_flash = 0.0;
float   test_kWh_from_read  = 0.0;
/* Define Memory pool for Ethernet info  */
//osMemoryPoolId_t EthernetEthPool;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI3_Init(void);
static void MX_CRC_Init(void);
static void MX_IWDG_Init(void);
void StartDefaultTask(void *argument);
void vSensorsTask(void *argument);
void vRW_Settings_Tas(void *argument);
void vOneSecondTickTask(void *argument);
void vMaintEthTask(void *argument);
void vDebugMemUsage(void *argument);
void httpServ(void *argument);
void vMQTT_Task(void *argument);
void vResetWatchDog(void *argument);
void vSendBroadcast(void *argument);

/* USER CODE BEGIN PFP */
void EthMutexTake(void);
void EthMutexRelease (void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){

	if (huart->Instance == USART2){
		if (Size == 24){
			if (!osMessageQueueGetCount(rowPowerSensorQHandle)){
				osMessageQueuePut(rowPowerSensorQHandle, &data_bufer, 0, 0);
			}
			HAL_UARTEx_ReceiveToIdle_IT(&huart2, data_bufer,  24);
		}
	}
}

void EthMutexTake(void){
	osMutexAcquire(NetworkHandle, osWaitForever);
}

void EthMutexRelease(void){
	osMutexRelease(NetworkHandle);
}

void LfsMutexTake(void){
	osMutexAcquire(LFSHandle, osWaitForever);
}

void LfsMutexRelease(void){
	osMutexRelease(LFSHandle);
}

void SocketMutexTake(void){
	osMutexAcquire(SocketHandle, osWaitForever);
}

void SocketMutexRelease(void){
	osMutexRelease(SocketHandle);
}

void ServiceSockMutexTake(){
	osMutexAcquire(ServiceSocketHandle, osWaitForever);
}

void ServiceSockMutexRelease(){
	osMutexRelease(ServiceSocketHandle);
}

void PowerON_HLW8032(){
	HAL_GPIO_WritePin(GPIOA, enable_power_isolator_Pin,GPIO_PIN_RESET);
}

void PowerOFF_HLW8032(){
	HAL_GPIO_WritePin(GPIOA, enable_power_isolator_Pin,GPIO_PIN_SET);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	__disable_irq();
	SCB->VTOR = (uint32_t)0x08000000 | (0x08010000 & (uint32_t)0x1FFFFF80);
	 //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x08010000);
	__enable_irq();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  dns_service_reg_cb_net_ready(assigned_ip);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_MBEDTLS_Init();
  MX_CRC_Init();
  MX_IWDG_Init();
  /* Call PreOsInit function */
  MX_MBEDTLS_Init();
  /* USER CODE BEGIN 2 */
  /* add EthernetEthPool */
//  EthernetEthPool = osMemoryPoolNew(1, sizeof(Ethernet_info_struct), NULL);
//  if (EthernetEthPool == NULL) Error_Handler();

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of Network */
  NetworkHandle = osMutexNew(&Network_attributes);

  /* creation of LFS */
  LFSHandle = osMutexNew(&LFS_attributes);

  /* creation of Socket */
  SocketHandle = osMutexNew(&Socket_attributes);

  /* creation of ServiceSocket */
  ServiceSocketHandle = osMutexNew(&ServiceSocket_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of rowPowerSensorQ */
  rowPowerSensorQHandle = osMessageQueueNew (1, 30, &rowPowerSensorQ_attributes);

  /* creation of EthernetInfoQ */
  EthernetInfoQHandle = osMessageQueueNew (1, sizeof(Ethernet_info_struct), &EthernetInfoQ_attributes);

  /* creation of PowerDataQ */
  PowerDataQHandle = osMessageQueueNew (1, sizeof(PowerSensStruct), &PowerDataQ_attributes);

  /* creation of Curr_sensor_settings */
  Curr_sensor_settingsHandle = osMessageQueueNew (1, sizeof(P_sens_sett_struct), &Curr_sensor_settings_attributes);

  /* creation of mqttQ */
  mqttQHandle = osMessageQueueNew (1, sizeof(MQTT_cred_struct), &mqttQ_attributes);

  /* creation of mb_tcp_settingsQ */
  mb_tcp_settingsQHandle = osMessageQueueNew (1, sizeof(ModBusTCP_struct), &mb_tcp_settingsQ_attributes);

  /* creation of uptimeQ */
  uptimeQHandle = osMessageQueueNew (1, sizeof(uint32_t), &uptimeQ_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of SensorsTask */
  SensorsTaskHandle = osThreadNew(vSensorsTask, NULL, &SensorsTask_attributes);

  /* creation of RW_Settings_Tas */
  RW_Settings_TasHandle = osThreadNew(vRW_Settings_Tas, NULL, &RW_Settings_Tas_attributes);

  /* creation of oneSecondTickTa */
  oneSecondTickTaHandle = osThreadNew(vOneSecondTickTask, NULL, &oneSecondTickTa_attributes);

  /* creation of maintEthTask */
  maintEthTaskHandle = osThreadNew(vMaintEthTask, NULL, &maintEthTask_attributes);

  /* creation of DebugMemUsageT */
  DebugMemUsageTHandle = osThreadNew(vDebugMemUsage, NULL, &DebugMemUsageT_attributes);

  /* creation of httpServTask */
  httpServTaskHandle = osThreadNew(httpServ, NULL, &httpServTask_attributes);

  /* creation of mqttClientTask */
  mqttClientTaskHandle = osThreadNew(vMQTT_Task, NULL, &mqttClientTask_attributes);

  /* creation of resetWatchDog */
  resetWatchDogHandle = osThreadNew(vResetWatchDog, NULL, &resetWatchDog_attributes);

  /* creation of SendBroadcast */
  SendBroadcastHandle = osThreadNew(vSendBroadcast, NULL, &SendBroadcast_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

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
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
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
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

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
  huart2.Init.BaudRate = 4800;
  huart2.Init.WordLength = UART_WORDLENGTH_9B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_EVEN;
  huart2.Init.Mode = UART_MODE_RX;
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, enable_power_isolator_Pin|SPI_flash_cs_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Ethernet_reset_GPIO_Port, Ethernet_reset_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Ethernet_cs_GPIO_Port, Ethernet_cs_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : enable_power_isolator_Pin Ethernet_reset_Pin */
  GPIO_InitStruct.Pin = enable_power_isolator_Pin|Ethernet_reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_flash_cs_Pin */
  GPIO_InitStruct.Pin = SPI_flash_cs_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SPI_flash_cs_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Ethernet_cs_Pin */
  GPIO_InitStruct.Pin = Ethernet_cs_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Ethernet_cs_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_vSensorsTask */
/**
* @brief Function implementing the SensorsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vSensorsTask */
void vSensorsTask(void *argument)
{
  /* USER CODE BEGIN vSensorsTask */
	uint32_t			temp;
	uint8_t				array[30];
	PowerSensStruct		PowerData;
	P_sens_sett_struct	PowerSett;
	uint32_t			count = 0;
	float				old_resistance;


	PowerSett.resistance = 0.001;
	PowerSett.save = 0;
	//xQueueOverwrite(Curr_sensor_settingsHandle, (void *)&PowerSett);

	osDelay(delay5s);

	xQueuePeek(Curr_sensor_settingsHandle ,&PowerSett,0);
	old_resistance = PowerSett.resistance;
	PowerOFF_HLW8032();
	osDelay(delay0_5s);
	USART2->DR; //read data from register if exist
	HAL_UARTEx_ReceiveToIdle_IT(&huart2, data_bufer,  24);
	osDelay(delay1s);
	PowerON_HLW8032();

	sens_task_start:


	InitHLW8032(1880000, 1000, PowerSett.resistance);
  /* Infinite loop */
  for(;;)
  {
	if (osMessageQueueGet	(rowPowerSensorQHandle,&array,NULL, 1000) != osErrorTimeout ){
		if( RecvRawString((const unsigned char *)array) == 0){ // all OK if return 0
			test_kWh_from_read 				= GetKWh();
			PowerData.KWatt_h 				= GetKWh()+ test_kWh_from_flash;
			PowerData.Voltage 				= GetVoltage();
			PowerData.ApparPower 			= GetApparentPower();
			PowerData.ActivePower 			= GetActivePower();
			PowerData.Current 				= GetCurrent();
			PowerData.PowerFactor			= PowerFactor();
			PowerData.test_pulse_counter 	= GetTestPulse();
			PowerData.readed_counter 		= GetCountedPulse();
			PowerData.PF_reg				= GetPFReg();
			xQueueOverwrite(PowerDataQHandle, (void *)&PowerData);
		}
	}else{
		count++;
		while (HAL_UARTEx_ReceiveToIdle_IT(&huart2, data_bufer,  24) == HAL_ERROR){
			temp = USART2->DR;
			osThreadYield();
		}
	}
	osThreadYield();
    xQueuePeek(Curr_sensor_settingsHandle ,&PowerSett,0);
    if (PowerSett.resistance != old_resistance){
    	old_resistance = PowerSett.resistance;
    	goto sens_task_start;
    }
  }
  /* USER CODE END vSensorsTask */
}

/* USER CODE BEGIN Header_vRW_Settings_Tas */
/**
* @brief Function implementing the RW_Settings_Tas thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_vRW_Settings_Tas */
void vRW_Settings_Tas(void *argument)
{
  /* USER CODE BEGIN vRW_Settings_Tas */
	uint8_t 				buff_read[256];
	uint8_t 				buff_write[256];
	uint8_t 				lookheadbuf[256];
	P_sens_sett_struct		PowerSett;
	MQTT_cred_struct		MQTT_cred;
	ModBusTCP_struct		mb_tcp_sett;
	uint32_t				next_update = 20, time_counter = 0;
	PowerSensStruct			PowerData;
	float					KWatt_h_old = 0;

	SPI_flash_set(hspi1);
	SPI_flash_reg_cb(SPI_flash_select, SPI_flash_deselect, SPI_flash_read_byte, SPI_flash_send_byte);
	spi_fs_init(buff_read, buff_write, lookheadbuf, 256 );
	spi_fs_init_mutex(LfsMutexTake, LfsMutexRelease);


	if (spi_fs_mount() < 0){
		spi_fs_format();
		spi_fs_mount();
	}

	if (0 < spi_fs_file_size(POW_SETT_FILE)){
		spi_fs_read_file_offset(POW_SETT_FILE, &PowerSett, 0, sizeof(PowerSett));
		xQueueOverwrite(Curr_sensor_settingsHandle ,(void *)&PowerSett);
	}else{
		PowerSett.resistance 	= DEFAULT_SHUNT_RESISTANSE;
		PowerSett.save 			= 1;
		xQueueOverwrite(Curr_sensor_settingsHandle ,(void *)&PowerSett);
	}

	if (0 < spi_fs_file_size(MQTT_SETT_FILE)){
		spi_fs_read_file_offset(MQTT_SETT_FILE, &MQTT_cred, 0, sizeof(MQTT_cred));
		xQueueOverwrite(mqttQHandle ,(void *)&MQTT_cred);
	}else{
		MQTT_cred.save 			= 1;
		MQTT_cred.enable		= 0;
		MQTT_cred.login[0]		= '\0';
		MQTT_cred.pass[0]		= '\0';
		MQTT_cred.uri[0]		= '\0';
		xQueueOverwrite(mqttQHandle ,(void *)&MQTT_cred);
	}

	if (0 < spi_fs_file_size(MB_TCP_SETT_FILE)){
		spi_fs_read_file_offset(MB_TCP_SETT_FILE, &mb_tcp_sett, 0, sizeof(mb_tcp_sett));
		xQueueOverwrite(mb_tcp_settingsQHandle ,(void *)&mb_tcp_sett);
	}else{
		mb_tcp_sett.enable 		= 0;
		mb_tcp_sett.save		= 1;
	}

	if (0 < spi_fs_file_size(KW_COUNT_STOR_FILE)){
		spi_fs_read_file_offset(KW_COUNT_STOR_FILE, &test_kWh_from_flash, 0, sizeof(test_kWh_from_flash));
		KWatt_h_old = test_kWh_from_flash;
	}else{
		test_kWh_from_flash = 0.0;
		KWatt_h_old 		= 0.0;
		spi_fs_over_write_file(KW_COUNT_STOR_FILE, &test_kWh_from_flash, sizeof(test_kWh_from_flash));

	}

	spi_fs_mkdir("/web");
	spi_fs_remove_recurcuve_in("/firmware");
	spi_fs_mkdir("/firmware");
	/* Infinite loop */

  for(;;)
  {
	  xQueuePeek(Curr_sensor_settingsHandle, (void *)&PowerSett, 0);
	  if (PowerSett.save){
		  PowerSett.save = 0;
		  spi_fs_over_write_file(POW_SETT_FILE, &PowerSett, sizeof(PowerSett));
		  xQueueOverwrite(Curr_sensor_settingsHandle ,(void *)&PowerSett);
	  }

	  xQueuePeek(mqttQHandle, (void *)&MQTT_cred, 0);
	  if (MQTT_cred.save){
		  MQTT_cred.save = 0;
		  spi_fs_over_write_file(MQTT_SETT_FILE, &MQTT_cred, sizeof(MQTT_cred));
		  xQueueOverwrite(mqttQHandle ,(void *)&MQTT_cred);
	  }

	  xQueuePeek(mb_tcp_settingsQHandle, (void *)&mb_tcp_sett, 0);
	  if (mb_tcp_sett.save){
		  mb_tcp_sett.save = 0;
		  spi_fs_over_write_file(MB_TCP_SETT_FILE, &mb_tcp_sett, sizeof(mb_tcp_sett));
	  }

	  xQueuePeek(PowerDataQHandle, (void *)&PowerData, 0);

	  if ((next_update < time_counter) || ((PowerData.KWatt_h - KWatt_h_old)> 1.0)){
		  spi_fs_over_write_file(KW_COUNT_STOR_FILE, &PowerData.KWatt_h, sizeof(PowerData.KWatt_h));
		  next_update += ENERGY_VALUE_SAVE_INTERVAL;
	  }

	  time_counter ++;
    osDelay(delay1s);
  }
  /* USER CODE END vRW_Settings_Tas */
}

/* USER CODE BEGIN Header_vOneSecondTickTask */
/**
* @brief Function implementing the oneSecondTickTa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vOneSecondTickTask */
void vOneSecondTickTask(void *argument)
{
  /* USER CODE BEGIN vOneSecondTickTask */
	uint32_t seconds;
	seconds = 0;
  /* Infinite loop */
  for(;;)
  {
	seconds++ ;
	DHCP_time_handler();
	httpServer_time_handler();
	dns_service_increment_second();
	xQueueOverwrite(uptimeQHandle, (void *)&seconds);
    osDelay(delay1s);
  }
  /* USER CODE END vOneSecondTickTask */
}

/* USER CODE BEGIN Header_vMaintEthTask */
/**
* @brief Function implementing the maintEthTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vMaintEthTask */
void vMaintEthTask(void *argument)
{
  /* USER CODE BEGIN vMaintEthTask */

	  wiz_NetInfo 			NetInfo;
	  Ethernet_info_struct	EthernetInfo;
	  uint8_t 				i;
	  uint8_t 				DHCP_DATABUF[SOCKET_BUFF_SIZE];
	  uint8_t				DNS_buff[SOCKET_BUFF_SIZE];

	  memset(&EthernetInfo, 0, sizeof(EthernetInfo));
	  memset(&NetInfo, 		0, sizeof(NetInfo));

	  NetInfo.mac[0]	= 0x40;
	  NetInfo.mac[1]	= 0x08;
	  NetInfo.mac[2]	= *(uint8_t*)(UID_BASE);
	  NetInfo.mac[3]	= *(uint8_t*)(UID_BASE + 0x01);
	  NetInfo.mac[4]	= *(uint8_t*)(UID_BASE + 0x02);
	  NetInfo.mac[5]	= *(uint8_t*)(UID_BASE + 0x03);

	  memcpy(&EthernetInfo.mac, &NetInfo.mac, sizeof(NetInfo.mac));
	  //for(i = 0; i < 6; i++){
	  //	EthernetInfo.mac[i] = NetInfo.mac[i];
	  //}

		//todo read from flash ip, netmask, dns, gateway

		//NetInfo.ip[0]	= 0, NetInfo.ip[1] 	= 0, NetInfo.ip[2] 	= 0, NetInfo.ip[3] 	= 0;
		//NetInfo.sn[0] 	= 0, NetInfo.sn[1] 	= 0, NetInfo.sn[2] 	= 0, NetInfo.sn[3] 	= 0;
		//NetInfo.gw[0] 	= 0, NetInfo.gw[1] 	= 0, NetInfo.gw[2] 	= 0, NetInfo.gw[3] 	= 0;
		//NetInfo.dns[0] 	= 0, NetInfo.dns[1] = 0, NetInfo.dns[2] = 0, NetInfo.dns[3] = 0;
		NetInfo.dhcp 	= NETINFO_DHCP;
		// TODO rewrite with memcpy function

		memcpy(&EthernetInfo.ip, &NetInfo.ip, sizeof(NetInfo.ip));
		memcpy(&EthernetInfo.sn, &NetInfo.sn, sizeof(NetInfo.sn));
		memcpy(&EthernetInfo.gw, &NetInfo.gw, sizeof(NetInfo.gw));
		memcpy(&EthernetInfo.dns, &NetInfo.dns, sizeof(NetInfo.dns));
		/*
		for(i = 0; i < 4; i++){
							EthernetInfo.ip[i] 	= NetInfo.ip[i];
							EthernetInfo.sn[i] 	= NetInfo.sn[i];
							EthernetInfo.gw[i] 	= NetInfo.gw[i];
							EthernetInfo.dns[i] = NetInfo.dns[i];
						}
*/
	  Reg_eth_spi(hspi3);
	  w5500_reset_cb(Eth_reset_on, Eth_reset_off);
	  w5500_delay_cb(osDelay);
	  w5500_lib_init(&NetInfo);
	  reg_wizchip_spi_cbfunc(Eth_spi_resv_byte, Eth_spi_send_byte);
	  reg_wizchip_cs_cbfunc(Eth_spi_select, Eth_spi_deselect);
	  reg_wizchip_cris_cbfunc(EthMutexTake, EthMutexRelease);
	  reg_dhcp_cbfunc(Callback_IPAssigned, Callback_IPAssigned, Callback_IPConflict);
	  dns_service_init(SERVICE_SOCKET, (uint8_t *)DNS_buff, SOCKET_BUFF_SIZE);
	  dns_service_reg_cb_net_ready(assigned_ip);
	  dns_service_reg_cb_mutex(ServiceSockMutexTake, ServiceSockMutexRelease);


  /* Infinite loop */
  for(;;)
  {
		EthernetInfo.dhcp = NetInfo.dhcp;
		EthernetInfo.link = 0;

		if (w5500_init() != 0)continue; //try from begin in fail case
		vTaskDelay(delay0_5s);
		setSHAR(NetInfo.mac);			//set mac address

		if (NetInfo.dhcp == NETINFO_DHCP){
			DHCP_init(DHCP_SOCKET, DHCP_DATABUF);
			//todo DNS_init();
		}else{
			network_init();
			set_ip_aasigned();
		}

		for(;;)
		{
			if (NetInfo.dhcp == NETINFO_DHCP){

			}
//xSemaphoreTake(SocketMutex, portMAX_DELAY);
			//osMutexAcquire(NetworkHandle, osWaitForever);
			SocketMutexTake();
			dhcp_rutine();

			if (!link_status()){
				NetInfo.ip[0]	= 0, NetInfo.ip[1] 	= 0, NetInfo.ip[2] 	= 0, NetInfo.ip[3] 	= 0;
				NetInfo.sn[0] 	= 0, NetInfo.sn[1] 	= 0, NetInfo.sn[2] 	= 0, NetInfo.sn[3] 	= 0;
				NetInfo.gw[0] 	= 0, NetInfo.gw[1] 	= 0, NetInfo.gw[2] 	= 0, NetInfo.gw[3] 	= 0;
				NetInfo.dns[0] 	= 0, NetInfo.dns[1] = 0, NetInfo.dns[2] = 0, NetInfo.dns[3] = 0;

//xSemaphoreGive(SocketMutex);
				//osMutexRelease(NetworkHandle);
				SocketMutexRelease();

				for(i = 0; i < 4; i++){
					EthernetInfo.ip[i] 	= NetInfo.ip[i];
					EthernetInfo.sn[i] 	= NetInfo.sn[i];
					EthernetInfo.gw[i] 	= NetInfo.gw[i];
					EthernetInfo.dns[i] = NetInfo.dns[i];
				}
				EthernetInfo.link 	= 0;
				xQueueOverwrite(EthernetInfoQHandle, (void *)&EthernetInfo);
				break;
			}

			for(i = 0; i < 4; i++){//todo rewrite for get info from dhcp calbac
				EthernetInfo.ip[i] 	= NetInfo.ip[i];
				EthernetInfo.sn[i] 	= NetInfo.sn[i];
				EthernetInfo.gw[i] 	= NetInfo.gw[i];
				EthernetInfo.dns[i] = NetInfo.dns[i];
			}

			EthernetInfo.link 		= 1;
			EthernetInfo.speed 		= link_speed();
			EthernetInfo.duplex 	= link_duplex();
			EthernetInfo.lease_s	= getDHCPLeasetime();

//xSemaphoreGive(SocketMutex);
			//osMutexRelease(NetworkHandle);
			//ctlnetwork(CN_GET_NETINFO, &NetInfo);
			SocketMutexRelease();

			if (NetInfo.ip[0]== 0){
				xQueueOverwrite(EthernetInfoQHandle, (void *)&EthernetInfo);
				osDelay(delay1s);
				continue;
			}

			// SET DNS SERVER IP
			dns_service_set_dns_ip((uint8_t*)&EthernetInfo.dns);
			xQueueOverwrite(EthernetInfoQHandle, (void *)&EthernetInfo);
			osDelay(delay1s);
		}
    osDelay(1);
  }
  /* USER CODE END vMaintEthTask */
}

/* USER CODE BEGIN Header_vDebugMemUsage */
/**
* @brief Function implementing the DebugMemUsage thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vDebugMemUsage */
void vDebugMemUsage(void *argument)
{
  /* USER CODE BEGIN vDebugMemUsage */
	uint32_t	mem;
  /* Infinite loop */
  for(;;)
  {
	  mem = osThreadGetStackSpace(defaultTaskHandle);
	  mem = osThreadGetStackSpace(SensorsTaskHandle);
	  mem = osThreadGetStackSpace(RW_Settings_TasHandle);
	  mem = osThreadGetStackSpace(oneSecondTickTaHandle);
	  mem = osThreadGetStackSpace(maintEthTaskHandle);
	  mem = osThreadGetStackSpace(DebugMemUsageTHandle);
	  mem = osThreadGetStackSpace(httpServTaskHandle);
	  mem = osThreadGetStackSpace(NULL);
	  mem = osThreadGetStackSpace(NULL);
	  mem = osThreadGetStackSpace(NULL);
	  osDelay(delay1s);
  }
  /* USER CODE END vDebugMemUsage */
}

/* USER CODE BEGIN Header_httpServ */
/**
* @brief Function implementing the httpServTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_httpServ */
void httpServ(void *argument)
{
  /* USER CODE BEGIN httpServ */
	Ethernet_info_struct	EthernetInfo;
	uint8_t 				socknumlist[] = {HTTP_SERVER_SOCKET, HTTP_SERVER_SOCKET1, HTTP_SERVER_SOCKET2};
	uint8_t 				http_buffer_rx[2048];
	uint8_t 				http_buffer_tx[2048];
	uint8_t 				http_nsockets = sizeof(socknumlist) / sizeof(socknumlist[0]);
	uint8_t					i;

	httpServer_init(http_buffer_tx, http_buffer_rx, http_nsockets, socknumlist);		// Tx/Rx buffers (2 kB) / The number of W5500 chip H/W sockets in use
	reg_external_post_cgi_processor(http_post_cgi_processor);
	reg_external_get_cgi_processor(http_get_cgi_processor);

	http_parse_params_init(PowerDataQHandle,			PowrData);
	http_parse_params_init(Curr_sensor_settingsHandle,	PowrSensSett);
	http_parse_params_init(mqttQHandle,					MQTT);
	http_parse_params_init(mb_tcp_settingsQHandle,		ModBusTCP);
	http_parse_params_init(uptimeQHandle,				Uptime);


	reg_httpServer_webContent((uint8_t *)"index.html",			(uint8_t *)index_page);
	reg_httpServer_webContent((uint8_t *)"power_settings.html",	(uint8_t *)setting_resistance_sens_page);
	reg_httpServer_webContent((uint8_t *)"mqtt.html",			(uint8_t *)conf_page_mqtt);


  /* Infinite loop */
  for(;;)
  {
	  xQueuePeek(EthernetInfoQHandle, &EthernetInfo, 0);
	  if ((EthernetInfo.link == ETH_LINK_UP) && (assigned_ip() == true)){
		  for(i = 0 ; i < http_nsockets; i++){
			  SocketMutexTake();
			  httpServer_run(i); // HTTP Server handler
			  SocketMutexRelease();
			  //osDelay(delay0_1s);

		  }
	  }else{
		  osDelay(delay1s);
	  }
	  osDelay(delay0_1s);
	  //osDelay(delay0_1s);
  }
  /* USER CODE END httpServ */
}

/* USER CODE BEGIN Header_vMQTT_Task */
/**
* @brief Function implementing the mqttClientTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vMQTT_Task */
void vMQTT_Task(void *argument)
{
  /* USER CODE BEGIN vMQTT_Task */
	Ethernet_info_struct	EthernetInfo;
	MQTT_cred_struct		MQTT_cred;
	PowerSensStruct			PowerData;
	char 					MQTT_SEND_BUF[MQTT_BUF_LEN];
	char 					MQTT_READ_BUF[MQTT_BUF_LEN];
	char					topik_name[TOPIK_MAX_LEN];
	char					topik_payload[128];


	init_mqtt_call_mutex(SocketMutexTake, SocketMutexRelease);
  /* Infinite loop */
	for(;;)
	{
		osDelay(delay1s);
		xQueuePeek(EthernetInfoQHandle,  &EthernetInfo, 0);
		if ((EthernetInfo.link != ETH_LINK_UP) || (assigned_ip() != true)){
			continue;
		}
		xQueuePeek(mqttQHandle, &MQTT_cred, 0);
		while (MQTT_cred.enable == 0){
			osDelay(delay1s);
			xQueuePeek(mqttQHandle, &MQTT_cred, 0);
		}
		if (!MQTT_cred.enable) continue; //TODO mybe remove;
		if (mqtt_client_init(&EthernetInfo, &MQTT_cred, MQTT_SEND_BUF, MQTT_BUF_LEN, MQTT_READ_BUF, MQTT_BUF_LEN) != 0 ) {
			//TODO add message to log
			continue;
		}
		if (mqtt_client_connect() < 0) continue;
		if (mqtt_client_reg_dev_on_home_assist() != 0) continue;

		generate_status_topik(topik_name, 0);
		while (1){
			xQueuePeek(PowerDataQHandle, &PowerData, 0);
			generate_key_value_JSON(topik_payload, dev_class_energy, PowerData.KWatt_h);
			if (send_data_to_topik(topik_name, topik_payload) != 0 ) break;

			generate_key_value_JSON(topik_payload, dev_class_voltage, PowerData.Voltage);
			if (send_data_to_topik(topik_name, topik_payload) != 0 ) break;

			generate_key_value_JSON(topik_payload, dev_class_current, PowerData.Current);
			if (send_data_to_topik(topik_name, topik_payload) != 0 ) break;

			generate_key_value_JSON(topik_payload, dev_class_power_factor, PowerData.PowerFactor * 100);
			if (send_data_to_topik(topik_name, topik_payload) != 0 ) break;

			generate_key_value_JSON(topik_payload, dev_class_power, PowerData.ActivePower);
			if (send_data_to_topik(topik_name, topik_payload) != 0 ) break;

			generate_key_value_JSON(topik_payload, dev_class_apparent_power, PowerData.ApparPower);
			if (send_data_to_topik(topik_name, topik_payload) != 0 ) break;



			osDelay(delay30s);
		}
		osDelay(delay1s);
	}
  /* USER CODE END vMQTT_Task */
}

/* USER CODE BEGIN Header_vResetWatchDog */
/**
* @brief Function implementing the resetWatchDog thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vResetWatchDog */
void vResetWatchDog(void *argument)
{
  /* USER CODE BEGIN vResetWatchDog */
  /* Infinite loop */
  for(;;)
  {
	HAL_IWDG_Refresh(&hiwdg);
    osDelay(1);
  }
  /* USER CODE END vResetWatchDog */
}

/* USER CODE BEGIN Header_vSendBroadcast */
/**
* @brief Function implementing the SendBroadcast thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vSendBroadcast */
void vSendBroadcast(void *argument)
{
  /* USER CODE BEGIN vSendBroadcast */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END vSendBroadcast */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
