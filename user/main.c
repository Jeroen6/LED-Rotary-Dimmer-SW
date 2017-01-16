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
#include "pwm.h"
#include "controller.h"

/* Settings ------------------------------------------------------------------*/
#define ENABLE_READOUTPROTECTION	1		/// Enable to prevent reading of flash contents using jtag
#define ENABLE_FLASHSELFTEST			1		/// Enable to check flash integrity every boot

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/
Ctrl_t ch1_ctrlr, ch2_ctrlr;
Button_t ch1_btn, ch2_btn;

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
	pwm_init();
	eeprom_init();
	controller_init(&ch1_ctrlr);
	controller_init(&ch2_ctrlr);
	button_init(&ch1_btn);
	button_init(&ch2_btn);
	
	// Superloop
	while(1){
		uint8_t t;
		// Execute
		t = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		ch1_ctrlr.button = button_execute(&ch1_btn, systime, t);
		t = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
		ch2_ctrlr.button = button_execute(&ch2_btn, systime, t);
		

		
		controller_execute(&ch1_ctrlr);
		controller_execute(&ch2_ctrlr);
		
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
