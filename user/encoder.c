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
#include "encoder.h"

/* Settings ------------------------------------------------------------------*/

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/

/* Private functions ---------------------------------------------------------*/
static void encoder_init_tim1(void){
	#warning TODO: remove magic bytes.
	TIM1->CR1   = 0x0001;     // CEN(Counter ENable)='1'     < TIM control register 1
	TIM1->SMCR  = 0x0003;     // SMS='011' (Encoder mode 3)  < TIM slave mode control register
	TIM1->CCMR1 = 0xF1F1;     // CC1S='01' CC2S='01'         < TIM capture/compare mode register 1
	TIM1->CCMR2 = 0x0000;     //                             < TIM capture/compare mode register 2
	TIM1->CCER  = 0x0011;     // CC1P CC2P                   < TIM capture/compare enable register
	TIM1->PSC   = 0x0000;     // Prescaler = (0+1)           < TIM prescaler
	TIM1->ARR   = 0xffffffff; // reload at 0xfffffff         < TIM auto-reload register
	TIM1->CNT = 0x0000;  			// reset the counter before we use it  
}

static void encoder_init_tim2(void){
	TIM2->CR1   = 0x0001;     // CEN(Counter ENable)='1'     < TIM control register 1
	TIM2->SMCR  = 0x0003;     // SMS='011' (Encoder mode 3)  < TIM slave mode control register
	TIM2->CCMR1 = 0xF1F1;     // CC1S='01' CC2S='01'         < TIM capture/compare mode register 1
	TIM2->CCMR2 = 0x0000;     //                             < TIM capture/compare mode register 2
	TIM2->CCER  = 0x0011;     // CC1P CC2P                   < TIM capture/compare enable register
	TIM2->PSC   = 0x0000;     // Prescaler = (0+1)           < TIM prescaler
	TIM2->ARR   = 0xffffffff; // reload at 0xfffffff         < TIM auto-reload register
	TIM2->CNT = 0x0000;  			// reset the counter before we use it  
}
/* Exported functions --------------------------------------------------------*/
/**
 * @brief Initialize all encoder inputs with corresponding timer.
 */
void encoder_init_all(){
	
}

/**
 * @brief Read relative encoder movement since last poll.
 * @param[in] encoder index	0 to ENCODER_COUNT-1
 */
void read_relative(uint8_t encoder){
	
}

/**
 * @brief Read absolute encoder position since reset_absolute().
 * @param[in] encoder	index 0 to ENCODER_COUNT-1
 */
void read_absolute(uint8_t encoder);

/**
 * @brief Reset absolute encoder position.
 * @param[in] encoder	index 0 to ENCODER_COUNT-1
 */
void reset_absolute(uint8_t encoder){
	
}
/**
 * @}
 */
