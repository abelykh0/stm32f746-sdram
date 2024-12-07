/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    bsp_driver_sdram.h (based on stm32756g_eval_sdram.h)
  * @brief   This file contains the common defines and functions prototypes for
  *          the bsp_driver_sdram.c driver.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F7_SDRAM_H
#define __STM32F7_SDRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_sdram.h"

/* USER CODE BEGIN 0 */

/** 
  * @brief  SDRAM status structure definition  
  */     
#define   SDRAM_OK         ((uint8_t)0x00)
#define   SDRAM_ERROR      ((uint8_t)0x01)

/* Exported constants --------------------------------------------------------*/ 

#define SDRAM_DEVICE_ADDR  ((uint32_t)0xD0000000)
#define SDRAM_DEVICE_SIZE  ((uint32_t)0x800000)  /* SDRAM device size */

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8  */
/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16 */
/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_32 */

/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_2 */
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */   

/*
 * sdram memory requires to be refreshed at a specific interval called "Refresh Interval Time" (tREFI or tREF) in the datasheet. For the used sdram module
 * this refresh interval is 15,6 us (4096 refresh cycles every 64ms). The interval is configured in the sdram controller in number of SDCLK cycles.
 * Having the SDCLK set to 108 MHz (we have HCLK set to 216 MHz and SDCLK to "HCLK/2"), this means we need to do a refresh every 1310 clock cycles:
 *
 *    108,000,000 Hz * 0.0000156 s = 1685
 *
 * The refresh is done automatically by the SDRAM controller, we just need to load the value into a counter. To obtain a safe margin if an internal
 * refresh request occurs when a read request has been accepted, the counter must be decreased by 20.
 */
#define REFRESH_COUNT     ((uint32_t)1665)
   
#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF) 

/* DMA definitions for SDRAM DMA transfer */
/*
#define __DMAx_CLK_ENABLE     __HAL_RCC_DMA2_CLK_ENABLE
#define __DMAx_CLK_DISABLE    __HAL_RCC_DMA2_CLK_DISABLE
#define SDRAM_DMAx_CHANNEL    DMA_CHANNEL_0
#define SDRAM_DMAx_STREAM     DMA2_Stream0
#define SDRAM_DMAx_IRQn       DMA2_Stream0_IRQn
#define SDRAM_DMAx_IRQHandler DMA2_Stream0_IRQHandler
*/
   
/**
  * @brief  FMC SDRAM Mode definition register defines
  */

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


/* Exported functions --------------------------------------------------------*/   
uint8_t BSP_SDRAM_Init(void);
uint8_t BSP_SDRAM_ReadData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_ReadData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_WriteData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_WriteData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd);

/* USER CODE END 0 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_SDRAM_H */
