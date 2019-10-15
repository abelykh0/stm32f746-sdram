/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    bsp_driver_sdram.c (based on stm32756g_eval_sdram.c)
  * @brief   This file includes a generic SDRAM driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
  

#ifdef OLD_CODE
/* Kept to avoid issue when migrating old projects (as some user sections were renamed/changed). */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
#else

/* Includes ------------------------------------------------------------------*/
#include "bsp_driver_sdram.h"

/* Extern variables ----------------------------------------------------------*/
extern SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN Init */
/**
  * @brief  Initializes the SDRAM device 
  * @retval SDRAM status
  */
uint8_t BSP_SDRAM_Init(void)
{
  uint8_t sdramstatus = SDRAM_OK;
  
  /* place for custom code */
	FMC_SDRAM_CommandTypeDef command;
	command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK2;
	command.ModeRegisterDefinition = 0;

	/* Step 1: Configure a clock configuration enable command */
	command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
	command.AutoRefreshNumber      = 1;
	HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);

	/* Step 2: Insert 100 us minimum delay */
	/* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
	HAL_Delay(1);

	/* Step 3: Configure a PALL (precharge all) command */
	command.CommandMode            = FMC_SDRAM_CMD_PALL;
	command.AutoRefreshNumber      = 1;
	HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);

	/* Step 4: Configure an Auto Refresh command */
	command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.AutoRefreshNumber      = 8;
	HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);

	/* Step 5: Program the external memory mode register */
	command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
	command.AutoRefreshNumber      = 1;
	command.ModeRegisterDefinition = (uint32_t)
		SDRAM_MODEREG_BURST_LENGTH_1          |
		SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
		SDRAM_MODEREG_CAS_LATENCY_2           |
		SDRAM_MODEREG_OPERATING_MODE_STANDARD |
		SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
	HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);

	/* Step 6: Set the refresh rate counter */
	HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT);

	return sdramstatus;
}
/* USER CODE END Init */

/* USER CODE BEGIN BeforeReadSection */
/* can be used to modify / undefine following code or add code */
/* USER CODE END BeforeReadSection */

/**
  * @brief  Reads an mount of data from the SDRAM memory in polling mode. 
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status : SDRAM_OK or SDRAM_ERROR.
  */
uint8_t BSP_SDRAM_ReadData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize)
{ 
  uint8_t sdramstatus = SDRAM_OK;
  
  if(HAL_SDRAM_Read_32b(&hsdram1, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    sdramstatus = SDRAM_ERROR;
  }

  return sdramstatus;
}

/**
  * @brief  Reads an mount of data from the SDRAM memory in DMA mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status : SDRAM_OK or SDRAM_ERROR.
  */
uint8_t BSP_SDRAM_ReadData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize)
{ 
  uint8_t sdramstatus = SDRAM_OK;
  
  if(HAL_SDRAM_Read_DMA(&hsdram1, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    sdramstatus = SDRAM_ERROR;
  }
   
  return sdramstatus;
}

/* USER CODE BEGIN BeforeWriteSection */
/* can be used to modify / undefine following code or add code */
/* USER CODE END BeforeWriteSection */

/**
  * @brief  Writes an mount of data to the SDRAM memory in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status : SDRAM_OK or SDRAM_ERROR.
  */
uint8_t BSP_SDRAM_WriteData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize)
{ 
  uint8_t sdramstatus = SDRAM_OK;
  
  if(HAL_SDRAM_Write_32b(&hsdram1, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    sdramstatus = SDRAM_ERROR;
  }

  return sdramstatus;
}

/**
  * @brief  Writes an mount of data to the SDRAM memory in DMA mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status : SDRAM_OK or SDRAM_ERROR.
  */
uint8_t BSP_SDRAM_WriteData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize)
{ 
  uint8_t sdramstatus = SDRAM_OK;
  
  if(HAL_SDRAM_Write_DMA(&hsdram1, (uint32_t *)uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    sdramstatus = SDRAM_ERROR;
  }

  return sdramstatus;
}

/**
  * @brief  Sends command to the SDRAM bank.
  * @param  SdramCmd: Pointer to SDRAM command structure
  * @retval SDRAM status : SDRAM_OK or SDRAM_ERROR.
  */
uint8_t BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd)
{ 
  uint8_t sdramstatus = SDRAM_OK;
  
  if(HAL_SDRAM_SendCommand(&hsdram1, SdramCmd, SDRAM_TIMEOUT) != HAL_OK)
  {
    sdramstatus = SDRAM_ERROR;
  }

  return sdramstatus;
}

/* USER CODE BEGIN AdditionalCode */
/* user code can be inserted here */
/* USER CODE END AdditionalCode */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
