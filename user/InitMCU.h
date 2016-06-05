/**
  ******************************************************************************
  * @file    InitMCU.h
  * @author
  * @version V1.0.0
  * @date
  * @brief   
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INITMCU_H_
#define __INITMCU_H_
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

/* Exported variables---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
extern IWDG_HandleTypeDef IWDG_handle;

/* Private define ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int BootCheck(void);
int InitMCU(void);
int InitGPIO(void);

#endif /* __INITMCU_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
