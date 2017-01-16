/**
  ******************************************************************************
  * @file    encoder.h
  * @author
  * @version V1.0.0
  * @date		 May 2016
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENCODER_H_
#define __ENCODER_H_
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

/* Settings ------------------------------------------------------------------*/
#define ENCODER_COUNT		2
/* Exported variables---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void encoder_init_all(void);
int32_t encoder_read_relative(uint8_t encoder);
int32_t encoder_read_log(uint8_t encoder);

#endif /* __ENCODER_H_ */
