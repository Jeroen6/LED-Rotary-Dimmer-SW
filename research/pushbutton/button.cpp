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
#include "button.h"

/* Settings ------------------------------------------------------------------*/
const ButtonSetting_t button_default_settings = {
	/* interval		  */	20,
	/* idle_time 	  */	2000, 
	/* dead_time 	  */	300,	
	/* min_low_time */	20,
	/* short_time	  */	2000, 
	/* long_time	  */	5000, 
	/* time_max     */	8192, 
};

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/**
 * @brief Initialize a button instance.
 * @note The default settings are loaded.
 */
void button_init(Button_t *instance){
	instance->settings 	= &button_default_settings;
	instance->nextrun 	= 0;
	instance->x_1 			= 1;
	instance->y_0 			= button_state_undef;
	instance->low_time 	= 0;
	instance->high_time	= 0xFFFF;
	instance->counter 	= 0;
	instance->emitted	 	= 0; 
	instance->flags 		= BUTTON_ENABLE_ALL;
}

/**
 * @brief Assign the default button settings.
 */
void button_defaults(Button_t *instance){
	instance->settings 	= &button_default_settings;
}

/**
 * @brief Initialize a button instance.
 */
ButtonState button_execute(Button_t *instance, uint32_t systime, uint8_t button){
	// Return to idle after capture, even if called to soon.
	if( instance->y_0 >= button_single ){
		instance->y_0 = button_state_idle;
	}			
	if(systime >= instance->nextrun ){
		instance->nextrun += instance->settings->interval;
		// Locals:
		uint8_t x_0 = button;
		uint8_t go_idle = 0;
		
		// Default state is always busy
		instance->y_0 = button_state_busy;
		
		// Increment timers, saturating at instance->settings->time_max
		if( x_0 == 0 ){ 
			instance->low_time += instance->settings->interval;
			if( instance->low_time > instance->settings->time_max ){
				instance->low_time = instance->settings->time_max; 
			}
		}
		if( x_0 == 1 ){ 
			instance->high_time += instance->settings->interval;
			if( instance->high_time > instance->settings->time_max ){
				instance->high_time = instance->settings->time_max; 
			}
		}
		
		// Determine edge
		// Rising edge
		if(instance->x_1 < x_0)
		{
			// Restart instance->high_time instance->counter
			instance->high_time = 0;
			// Go idle after long.
			if( instance->low_time > instance->settings->short_time ){
				go_idle = 1;
			}
		}
		else
		// Falling edge	
		if(instance->x_1 > x_0)
		{
			// Test for fast sequence
			if( instance->counter > 0 && !(instance->flags & (BUTTON_ENABLE_MULTI)) ){
				// Capture single event, and reset.
				if( instance->low_time >= instance->settings->min_low_time ){
					instance->y_0 = button_single;
					go_idle = 1;
				}
			}
			// Count valid edges
			if( instance->low_time >= instance->settings->min_low_time ) instance->counter++;
			instance->low_time = 0;
		}
		else
		{
			// No edge
			if( x_0 > 0 ){
				// state high
				// Test if dead time has passed and minimum low time was reached.
				if( instance->high_time >= instance->settings->dead_time && instance->low_time >= instance->settings->min_low_time ){
					if(instance->counter == 1 && instance->flags & BUTTON_ENABLE_SINGLE){
					// Capture single press event and go idle.
						instance->y_0 = button_single;
					}else
					if(instance->counter == 2 && instance->flags & BUTTON_ENABLE_MULTI){
						instance->y_0 = button_double;
					}
					if(instance->counter == 3 && instance->flags & BUTTON_ENABLE_MULTI){
						instance->y_0 = button_triple;
					}
					go_idle = 1;
				}						
				// Test if idle time has passed.
				if( instance->high_time > instance->settings->idle_time ){
					instance->y_0 = button_state_idle;
					instance->counter = 0;
				}
			}else{
				// state low, reset high timer
				if( instance->low_time >= instance->settings->time_max ){
					instance->y_0 = button_state_error;
				}else{
					instance->high_time = 0;
					// Capture long presses
					if(instance->low_time > instance->settings->short_time && instance->flags & (BUTTON_ENABLE_SHORT||BUTTON_ENABLE_LONG) ){
						if(instance->low_time > instance->settings->long_time && instance->flags & BUTTON_ENABLE_LONG ){ 
							if( instance->emitted == 1) {
								instance->emitted++;
								instance->y_0 = button_long;
							}
						}else{
							if( instance->emitted == 0) {
								instance->emitted++;
								instance->y_0 = button_short;
							}
						}
					}
				}						
			}
		}
		
		// Go idle (at next iteration) after valid capture
		if(go_idle > 0){
			// Saturate timer to put in idle
			instance->high_time = 8191;
			instance->low_time = 0;
			instance->x_1 = 1;
			instance->emitted = 0;
		}
						
		// Load x(t-1)
		instance->x_1 = x_0;
	}
	return instance->y_0;
}

/**
 * @brief Enable button capture modes
 */
void button_enable(Button_t *instance, uint8_t flags){
	instance->flags |= flags;
}

/**
 * @brief Disable button capture modes
 */
void button_disable(Button_t *instance, uint8_t flags){
	instance->flags &= ~flags;
}
/**
 * @}
 */











