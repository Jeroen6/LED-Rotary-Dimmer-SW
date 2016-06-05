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

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/**
 * @brief Initialize EEPROM module.
 */
void eeprom_init(void){
	
}

/**
 * @brief Select EEPROM chip.
 * @paramp[in] e			Chip I2C address.
 * @paramp[in] bytes	Chip size.
 */
void eeprom_chipselect(uint8_t e, uint16_t bytes){
	eeprom_current_chipselect = e
	eeprom_current_chipsize = bytes
}

/**
 * @brief Read from EEPROM chip.
 * @paramp[in] address	Chip I2C address.
 * @paramp[in] dst			Pointer to destination.
 * @retval 1	Success
 * @retval -1	Failure
 */
int eeprom_read(uint16_t address, uint8_t *dst){
	
}

/**
 * @brief Read from EEPROM chip.
 * @paramp[in] address	Chip I2C address.
 * @paramp[in] dst			Pointer to source.
 * @retval 1	Success
 * @retval -1	Failure
 */
int eeprom_write(uint16_t address, const uint8_t *src){
	
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
	
}
/**
 * @}
 */