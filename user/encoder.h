/**
  ******************************************************************************
  * @file    eeprom_M24C.h
  * @author
  * @version V1.0.0
  * @date		 May 2016
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEMPROM_M24C_H_
#define __EEMPROM_M24C_H_
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
void read_relative(uint8_t encoder);
void read_absolute(uint8_t encoder);
void reset_absolute(uint8_t encoder);

#endif /* __EEMPROM_M24C_H_ */
