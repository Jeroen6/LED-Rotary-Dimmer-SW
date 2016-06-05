/**
  ******************************************************************************
  * @file    main.h
  * @author
  * @version V1.0.0
  * @date
  * @brief   Header for main.c module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
#include <stdint.h>

/* Version ------------------------------------------------------------------*/
#warning Are these values up-to-date?
#define SW_VERSION		"V0.1"				// Software version string
#define SW_DECIMAL		0							// Incremental software decimal
#define HW_VERSION		"V1.0"				// Hardware version software is released on.

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/* Exported variables---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define systimeElapsedSince(start) ((systime) - (start))

/* Exported functions --------------------------------------------------------*/

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
