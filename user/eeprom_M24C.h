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
/* Exported variables---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define	EEPROM_M24C_DEV_TYPE_ID				0x50	//< Device Type Identifier 0b1010xxxx
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void eeprom_init(void);
void eeprom_chipselect(uint8_t e, uint16_t bytes);
int eeprom_read(uint16_t address, uint8_t *dst);
int eeprom_write(uint16_t address, const uint8_t *src);
int eeprom_read_block(uint16_t address, uint8_t *dst, uint16_t length);
int eeprom_write_block(uint16_t address, const uint8_t *src, uint16_t length);

#endif /* __EEMPROM_M24C_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
