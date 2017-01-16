/**
  ******************************************************************************
  * @file    pwm.c
  * @author  JLO
  * @version V1.0.0
  * @date    June 2016
  * @brief   Abstraction for PWM channels.
	*
	* @detail
	*
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "pwm.h"

/* Settings ------------------------------------------------------------------*/

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/
static TIM_HandleTypeDef tim3_handle = {
	TIM3,
	{
	/* Prescaler			    */     0x0000,
	/* CounterMode			  */     TIM_COUNTERMODE_UP,
	/* Period			        */     0xFFFF,
	/* ClockDivision			*/     TIM_CLOCKDIVISION_DIV1,
	/* RepetitionCounter	*/		 0x00
	},
	HAL_TIM_ACTIVE_CHANNEL_1 ,
	NULL,
	HAL_UNLOCKED,
	HAL_TIM_STATE_RESET
};
static TIM_OC_InitTypeDef tim3_ch1 = {
	/* OCMode       */ TIM_OCMODE_PWM1,
	/* Pulse        */ 0x7FFF,
	/* OCPolarity   */ TIM_OCPOLARITY_HIGH,
	/* OCNPolarity  */ TIM_OCNPOLARITY_HIGH,
	/* OCFastMode   */ TIM_OCFAST_DISABLE,
	/* OCIdleState  */ TIM_OCIDLESTATE_RESET,
	/* OCNIdleState */ TIM_OCNIDLESTATE_RESET
};

static TIM_HandleTypeDef tim15_handle = {
	TIM15,
	{
	/* Prescaler			    */ 0x0000,
	/* CounterMode			  */ TIM_COUNTERMODE_UP,
	/* Period			        */ 0xFFFF,
	/* ClockDivision			*/ TIM_CLOCKDIVISION_DIV1,
	/* RepetitionCounter	*/ 0x00
	},
	HAL_TIM_ACTIVE_CHANNEL_1 ,
	NULL,
	HAL_UNLOCKED,
	HAL_TIM_STATE_RESET
};
static TIM_OC_InitTypeDef tim15_ch1 = {
	/* OCMode       */ TIM_OCMODE_PWM1,
	/* Pulse        */ 0x7FFF,
	/* OCPolarity   */ TIM_OCPOLARITY_HIGH,
	/* OCNPolarity  */ TIM_OCNPOLARITY_HIGH,
	/* OCFastMode   */ TIM_OCFAST_DISABLE,
	/* OCIdleState  */ TIM_OCIDLESTATE_RESET,
	/* OCNIdleState */ TIM_OCNIDLESTATE_RESET
};

/* Private functions ---------------------------------------------------------*/
static void pwm_init_tim3(void){
	HAL_TIM_PWM_Init( &tim3_handle );
	HAL_TIM_PWM_ConfigChannel( &tim3_handle, &tim3_ch1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start( &tim3_handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel( &tim3_handle, &tim3_ch1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start( &tim3_handle, TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel( &tim3_handle, &tim3_ch1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start( &tim3_handle, TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel( &tim3_handle, &tim3_ch1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start( &tim3_handle, TIM_CHANNEL_4);
//	
//	CR1   = 
//	CR2   = 
//	SMCR  = 
//	DIER  = 
//	SR    = 
//	EGR   = 
//	CCMR1 = 
//	CCMR2 = 
//	CCER  = 
//	CNT   = 
//	PSC   = 
//	ARR   = 
//	RCR   = 
//	CCR1  = 
//	CCR2  = 
//	CCR3  = 
//	CCR4  = 
//	BDTR  = 
//	DCR   = 
//	DMAR  = 
//	OR    = 

}
static void pwm_init_tim15(void){
	HAL_TIM_PWM_Init( &tim15_handle );
	HAL_TIM_PWM_ConfigChannel( &tim15_handle, &tim15_ch1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start( &tim3_handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel( &tim15_handle, &tim15_ch1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start( &tim15_handle, TIM_CHANNEL_2);
}

/* Exported functions --------------------------------------------------------*/
/** 
 * @brief Initialize all used timers.
 */
void pwm_init(void){
	pwm_init_tim3();
	pwm_init_tim15();	
}

/** 
 * @brief Set new PWM value for given abstract channel.
 * @param[in] Abstracted channel number.
 * @param[in] Duty cycle (0-100% in 0-0xFFFF)
 */
void pwm_set(uint8_t ch, int16_t duty){
	
}

/**
 * @}
 */
