/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
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
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
# include "main.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define THREAD_STACK_SIZE 1024
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_SEMAPHORE semaphore_0;
uint8_t thread_stack[THREAD_STACK_SIZE];
TX_THREAD thread_ptr;
uint8_t thread_stack2[THREAD_STACK_SIZE];
TX_THREAD thread_ptr2;
uint8_t thread_stack3[THREAD_STACK_SIZE];
TX_THREAD thread_ptr3;

#define TRACEX_BUFFER_SIZE 64000
uint8_t tracex_buffer[64000] __attribute__ ((section(".trace")));
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
VOID my_thread_entry(ULONG intial_input);
VOID my_thread_entry2(ULONG intial_input);
VOID my_thread_entry3(ULONG intial_input);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */
TX_BYTE_POOL *byte_pool=(TX_BYTE_POOL*) memory_ptr;
(void)byte_pool;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
tx_thread_create(&thread_ptr,"my_thread",my_thread_entry,0x1234,thread_stack,THREAD_STACK_SIZE,15,15,1,TX_AUTO_START);
tx_thread_create(&thread_ptr2,"my_thread2",my_thread_entry2,0x1234,thread_stack2,THREAD_STACK_SIZE,15,15,1,TX_AUTO_START);
tx_thread_create(&thread_ptr3,"my_thread3",my_thread_entry3,0x1234,thread_stack3,THREAD_STACK_SIZE,15,15,1,TX_AUTO_START);
//tx_trace_enable(&tracex_buffer,TRACEX_BUFFER_SIZE,30);
tx_semaphore_create(&semaphore_0,"semaphore_0",0);
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
void my_thread_entry(ULONG inital_input){
	while(1){
		 HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port,LED_YELLOW_Pin);
		 HAL_Delay(100);
		 tx_thread_sleep(100);
	}
}

void my_thread_entry2(ULONG inital_input){
	while(1){
		 HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
		 HAL_Delay(200);
		 tx_thread_sleep(200);
	}
}

void my_thread_entry3(ULONG inital_input){
		ULONG current_value;
		TX_THREAD *first_suspended;
		ULONG suspended_count;
		TX_SEMAPHORE *next_semaphore;
		while (1)
		{
		// it will stop
		// in main.c-> we are waiaintg fot the btton prwss to start the semaphore
		/// I the above code we get that semaphore

		tx_semaphore_get(&semaphore_0, TX_NO_WAIT); // get the semaphore with suspension

		printf("user button pressed\r\n");
		UINT status=_tx_semaphore_info_get(&semaphore_0,
		NULL,
		&current_value,
		&first_suspended,
		&suspended_count,
		&next_semaphore );
		if(status==TX_SUCCESS){
		// access information
		printf("Current value: %lu\n\r\n\n",current_value++);

		}

		tx_thread_sleep(50);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_SET);

		}
}




/* USER CODE END 1 */
