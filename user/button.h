/**
  ******************************************************************************
  * @file    eeprom_M24C.h
  * @author
  * @version V1.0.0
  * @date		 May 2016
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H_
#define __BUTTON_H_
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
//#include "stm32f0xx.h"
//#include "stm32f0xx_hal.h"

/* Settings ------------------------------------------------------------------*/
/* Exported variables---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 * @brief Output types of button.
 */
typedef enum {
	// States
	button_state_undef 	= 0,	//< Button in undefined state, not initialized.
	button_state_idle 	= 1,	//< No button activity.	
	button_state_busy 	= 2,	//< Button activity, capturing event.
	button_state_error 	= 3,	//< Button error.
	// Events
	button_single = 10,	//< This value is returned one iteration on a single press event.
	button_double = 11,	//< This value is returned one iteration on a double press event.
	button_triple = 12, //< This value is returned one iteration on a triple press event.
	button_short 	= 30,	//< This value is returned one iteration on a short long press event.	
	button_long 	= 40,	//< This value is returned one iteration on a long press event.	
} ButtonState;

/**
 * @brief Settings used in button. These are allowed to be const.
 */
typedef struct {
	// Settings, 						// default; description
	uint16_t interval;			// 20;	 Samplerate interval in milliseconds.
	uint16_t idle_time; 		// 2000; Time after which the button is considered idle.	
	uint16_t dead_time; 		// 300;	 Time to wait for double keypress events.	
	uint16_t min_low_time;  // 20;	 Minimum low time.
	uint16_t short_time;		// 2000; Time to capture a short long press.
	uint16_t long_time;	    // 5000; Time to capture a long.
	uint16_t time_max;      // 8192; Saturate timer to this value.
} ButtonSetting_t;

/**
 * @brief Button instance.
 */
typedef struct {
	// Settings
	const ButtonSetting_t *settings;
	// Flags to select which button capture modes are active.
	uint8_t flags;
	// Operational variables. (systime)
	uint32_t nextrun;
	// Previous button state
	uint8_t x_1;
	// Time the button is low (pressed)
	uint16_t low_time;
	// Time the button is high
	uint16_t high_time;
	// Sequential press counter
	uint8_t counter;
	// Counter to prevent mutliple emits of short and long events.
	uint8_t emitted; 		
	// Last result
	ButtonState y_0;
} Button_t;

/* Defines -------------------------------------------------------------------*/
/** 
 * @brief Flags to change the active capture events of a button instance.
 * @defgroup Button Capture Flags
 * @{
 */
#define BUTTON_ENABLE_SINGLE			(1<<0)
#define BUTTON_ENABLE_MULTI				(1<<1)
#define BUTTON_ENABLE_SHORT				(1<<2)
#define BUTTON_ENABLE_LONG				(1<<3)
#define BUTTON_ENABLE_ALL					0x0F
/**
 * @}
 */
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void button_init(Button_t *instance);
void button_defaults(Button_t *instance);
ButtonState button_execute(Button_t *instance, uint32_t systime, uint8_t button);

void button_enable(Button_t *instance, uint8_t flags);
void button_disable(Button_t *instance, uint8_t flags);

#endif /* __BUTTON_H_ */


