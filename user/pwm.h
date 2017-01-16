/**
  ******************************************************************************
  * @file    pwm.h
  * @author
  * @version V1.0.0
  * @date		 May 2016
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWM_USER_H_
#define __PWM_USER_H_
#include <stdint.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

/* Settings ------------------------------------------------------------------*/
/* Exported variables---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define PWM_CH1			0
#define PWM_CH2			1	
#define PWM_CH1_R		2
#define PWM_CH1_G		3
#define PWM_CH2_R		4
#define PWM_CH2_G		5
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void pwm_init(void);
void pwm_set(uint8_t ch, int16_t duty);

#endif /* __PWM_USER_H_ */
