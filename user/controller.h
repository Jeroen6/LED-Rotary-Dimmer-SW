/**
  ******************************************************************************
  * @file    controller.h
  * @author
  * @version V1.0.0
  * @date		 June 2016
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTOROLLER_H_
#define __CONTOROLLER_H_
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "button.h"

/* Settings ------------------------------------------------------------------*/
/* Exported variables---------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct {
	uint16_t max;		//< Maximum channel brightness.
	uint16_t min;		//< Minumum channel brightness.
	uint16_t rise;	//< On slope speed.
	uint16_t fall;	//< Off slope speed.
	uint16_t last;	//< Last set brightness. (for resume behavior)
} Ctrl_cfg_t;

/** 
 * @brief Redefinition of Ctrl_t for pointer in typedef state_t.
 * @note 	Removing this would cause 
 * 				Ctrl_t to be unknown during state_t typedef.
 */
typedef struct Ctrl_t Ctrl_t;

/** 
 * @brief Pointer to state function.
 */
typedef void*(*state_t)(Ctrl_t *p);

/** 
 * @brief Structure of state machine instance.
 */
struct Ctrl_t {
	/* inputs */
	uint8_t enc_in;					//< Input index encoder.
	ButtonState button;	//< Input pushbutton.
	/* outputs */
	uint8_t ch_out;					//< PWM channel index for output channel.
	uint8_t enc_led;				//< PWM channel index for encoder led.
	/* state machine variables */
	state_t pstate;					//< Pointer to previous state function.
	state_t cstate;					//< Pointer to current state function.	
	/* Application variables */
	Ctrl_cfg_t settings;		//< Structure containing channel settings.
	/* Internal state variables */
};

/* Private define ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void controller_init(Ctrl_t *instance);
void controller_execute(Ctrl_t *instance);

#endif /* __CONTOROLLER_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
