/**
  ******************************************************************************
  * @file    main.c
  * @author  JLO
  * @version V1.0.0
  * @date    February 2015
  * @brief   Main superloop and initialisation routines
	*
	* @detail  The main function
	*					 - Set system flash read protection.
	*					 - Initialize system essential components
	*						+ Watchdog, Power Voltage Detector, Debug options
	*					 - Initialize the clock tree
	*						+ Setup main PLL and clock frequency to 72 MHz
	*					 - Verify flash integrity
	*					  + Blinkcode error on failure
	*					 - Initialize MCU
	*					 - Initialize modules.
	*						+ With special mode when keys are presssed during boot.
	*					 - Execute main superloop.
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "interrupts.h"
#include "memories.h"
#include "InitMCU.h"
#include "stm32f0xx_hal.h"

#include "encoder.h"
#include "button.h"
#include "eeprom_M24C.h"

/* Settings ------------------------------------------------------------------*/
#define ENABLE_READOUTPROTECTION	1		/// Enable to prevent reading of flash contents using jtag
#define ENABLE_FLASHSELFTEST			1		/// Enable to check flash integrity every boot

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void){
	BootCheck();
	InitMCU();
	InitGPIO();
	mem_initiate_parity();	// untested, option bytes not programmable with HAL, it seems.
	encoder_init_all();
	
	// Superloop
	while(1){
		// Wait for interrupt
		__wfi();
		// Watchdog, only location reloading of watchdog is allowed by design.
		HAL_IWDG_Refresh(&IWDG_handle);
	}
}

/**
 * @}
 */
/*****END OF FILE****/
