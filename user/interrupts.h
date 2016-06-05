/**
  ******************************************************************************
  * @file    Interrupts.h
  * @author
  * @version V1.0.0
  * @date		 May 2016
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPTS_H_
#define __INTERRUPTS_H_
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

/* Exported variables---------------------------------------------------------*/
extern volatile int exitCode;
/* Exported types ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup exitCodes
  * @{
  */
#define IT_EXITCODE_NORMAL			0		/// Normal exitcode.
#define IT_EXITCODE_HARDFAULT		-1	/// Set on exit by hardfault.
#define IT_EXITCODE_UNHANDLED		-2	/// Set on exit by unhandled exception.
#define IT_EXITCODE_WWDG				-3	/// Set on exit by WWDG interrupt.
#define IT_EXITCODE_IWDG				-3	/// Set on boot by bootCheck.
/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void IT_RemapVectorTable(void);

#endif /* __INTERRUPTS_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
