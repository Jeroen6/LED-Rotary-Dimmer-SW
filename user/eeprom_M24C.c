/**
  ******************************************************************************
  * @file    eeprom_M24C.c
  * @author  JLO
  * @version V1.0.0
  * @date    February 2015
  * @brief   API to use ST M24C EEPROM over I2C
	*
	* @detail  
	*					 
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "eeprom_M24C.h"

/* Settings ------------------------------------------------------------------*/
const uint8_t eeprom_default_chipselect 	= 0x0;
const uint16_t eeprom_default_chipsize 		= 0x0080;

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/
static uint8_t eeprom_current_chipselect 	= 0;
static uint16_t eeprom_current_chipsize 	= 0;
static I2C_HandleTypeDef I2C_Handle;

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/**
 * @brief Initialize EEPROM module.
 */
void eeprom_init(void){
	I2C_Handle.Instance = I2C1;
  I2C_Handle.Instance = I2C1;
  I2C_Handle.Init.Timing = 0x2000090E;
  I2C_Handle.Init.OwnAddress1 = 0;
  I2C_Handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  I2C_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2C_Handle.Init.OwnAddress2 = 0;
  I2C_Handle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  I2C_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2C_Handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&I2C_Handle);
	HAL_I2CEx_ConfigAnalogFilter(&I2C_Handle, I2C_ANALOGFILTER_ENABLE);
}

/**
 * @brief Select EEPROM chip.
 * @paramp[in] e			Chip I2C address.
 * @paramp[in] bytes	Chip size.
 */
void eeprom_chipselect(uint8_t e, uint16_t bytes){
	eeprom_current_chipselect = e;
	eeprom_current_chipsize = bytes;
}

/**
 * @brief Read from EEPROM chip.
 * @paramp[in] address	Chip I2C address.
 * @paramp[in] dst			Pointer to destination.
 * @retval 1	Success
 * @retval -1	Failure
 */
int eeprom_read(uint16_t address, uint8_t *dst){
	HAL_StatusTypeDef result;
	result = HAL_I2C_Mem_Read(&I2C_Handle, 
														eeprom_current_chipselect<<1,
														address,
														1,
														dst,
														1,
														10
														);
	switch(result){
		case HAL_OK:
			return 1;
		case HAL_ERROR:
			break;
		case HAL_BUSY:
			break;
		case HAL_TIMEOUT:
			break;
		default:
			break;		
	}
	return -1;
}

/**
 * @brief Read from EEPROM chip.
 * @paramp[in] address	Chip I2C address.
 * @paramp[in] dst			Pointer to source.
 * @retval 1	Success
 * @retval -1	Failure
 */
int eeprom_write(uint16_t address, const uint8_t *src){
	HAL_StatusTypeDef result;
	result = HAL_I2C_Mem_Write(&I2C_Handle, 
														eeprom_current_chipselect<<1,
														address,
														1,
														(uint8_t*)src,
														1,
														10
														);
	switch(result){
		case HAL_OK:
			return 1;
		case HAL_ERROR:
			break;
		case HAL_BUSY:
			break;
		case HAL_TIMEOUT:
			break;
		default:
			break;		
	}
	return -1;
}

/**
 * @brief Read from EEPROM chip.
 * @paramp[in] address	Chip I2C address.
 * @paramp[in] dst			Pointer to destination.
 * @paramp[in] length		Size of block to read.
 * @retval 1	Success
 * @retval -1	Failure
 */
int eeprom_read_block(uint16_t address, uint8_t *dst, uint16_t length){
	HAL_StatusTypeDef result;
	result = HAL_I2C_Mem_Read(&I2C_Handle, 
														eeprom_current_chipselect<<1,
														address,
														1,
														dst,
														length,
														10
														);
	switch(result){
		case HAL_OK:
			return 1;
		case HAL_ERROR:
			break;
		case HAL_BUSY:
			break;
		case HAL_TIMEOUT:
			break;
		default:
			break;		
	}
	return -1;
}

/**
 * @brief Read from EEPROM chip.
 * @paramp[in] address	Chip I2C address.
 * @paramp[in] dst			Pointer to source.
 * @paramp[in] length		Size of block to write.
 * @retval 1	Success
 * @retval -1	Failure
 */
int eeprom_write_block(uint16_t address, const uint8_t *src, uint16_t length){
	HAL_StatusTypeDef result;
	result = HAL_I2C_Mem_Write(&I2C_Handle, 
														eeprom_current_chipselect<<1,
														address,
														1,
														(uint8_t *)src,
														length,
														10
														);
	switch(result){
		case HAL_OK:
			return 1;
		case HAL_ERROR:
			break;
		case HAL_BUSY:
			break;
		case HAL_TIMEOUT:
			break;
		default:
			break;		
	}
	return -1;
}
/**
 * @}
 */
