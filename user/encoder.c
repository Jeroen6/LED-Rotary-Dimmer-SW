/**
  ******************************************************************************
  * @file    encoder.c
  * @author  JLO
  * @version V1.0.0
  * @date    June 2016
  * @brief   API to use ST M24C EEPROM over I2C
	*
	* @detail
	*
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* Private functions ---------------------------------------------------------*/
static void encoder_init_tim1(void){
	// CEN(Counter ENable)='1'     < TIM control register 1
	TIM1->CR1   = TIM_CR1_CEN;
	// SMS='011' (Encoder mode 3)  < TIM slave mode control register
	TIM1->SMCR  = TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0;
	// TIM capture/compare mode register 1
	// mode: CC1S='01' CC2S='01'         
	// filter: 1111: fSAMPLING = fDTS / 32, N = 8
	// prescaler: 00: no prescaler, capture is done each time an edge is detected on the capture input
	TIM1->CCMR1 = TIM_CCMR1_CC1S_1 |
								(TIM_CCMR1_IC1F 	& 0xF<<4 	) |
								(TIM_CCMR1_IC1PSC & 0x0<<2	) |
								TIM_CCMR1_CC2S_1 |
								(TIM_CCMR1_IC2F		& 0xF<<12 ) |
								(TIM_CCMR1_IC2PSC & 0x0<<2	);
	//                             < TIM capture/compare mode register 2
	TIM1->CCMR2 = 0x0000;
	// CC1P CC2P                   < TIM capture/compare enable register
	TIM1->CCER  = TIM_CCER_CC1E |	TIM_CCER_CC2E;
	// Prescaler = (0+1)           < TIM prescaler
	TIM1->PSC   = 0x0000;
	// reload at 0xfffffff         < TIM auto-reload register
	TIM1->ARR   = 0xffffffff;
	// reset the counter before we use it
	TIM1->CNT = 0x0000;
}

static void encoder_init_tim2(void){
	// CEN(Counter ENable)='1'     < TIM control register 1
	TIM2->CR1   = TIM_CR1_CEN;
	// SMS='011' (Encoder mode 3)  < TIM slave mode control register
	TIM2->SMCR  = TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0;
	// TIM capture/compare mode register 1
	// mode: CC1S='01' CC2S='01'         
	// filter: 1111: fSAMPLING = fDTS / 32, N = 8
	// prescaler: 00: no prescaler, capture is done each time an edge is detected on the capture input
	TIM2->CCMR1 = TIM_CCMR1_CC1S_1 |
								(TIM_CCMR1_IC1F 	& 0xF<<4 	) |
								(TIM_CCMR1_IC1PSC & 0x0<<2	) |
								TIM_CCMR1_CC2S_1 |
								(TIM_CCMR1_IC2F		& 0xF<<12 ) |
								(TIM_CCMR1_IC2PSC & 0x0<<2	);
	//                             < TIM capture/compare mode register 2
	TIM2->CCMR2 = 0x0000;
	// CC1P CC2P                   < TIM capture/compare enable register
	TIM2->CCER  = TIM_CCER_CC1E |	TIM_CCER_CC2E;
	// Prescaler = (0+1)           < TIM prescaler
	TIM2->PSC   = 0x0000;
	// reload at 0xfffffff         < TIM auto-reload register
	TIM2->ARR   = 0xffffffff;
	// reset the counter before we use it
	TIM2->CNT = 0x0000;
}
static uint32_t encoder_read_tim1(void){
	return TIM1->CNT;
}
static uint32_t encoder_read_tim2(void){
	return TIM1->CNT;
}


/* Settings ------------------------------------------------------------------*/
uint32_t (* const encoder[])(void) = {
	encoder_read_tim1,
	encoder_read_tim2
};

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/
static int32_t lastPoll[ENCODER_COUNT];

/* Exported functions --------------------------------------------------------*/
/**
 * @brief Initialize all encoder inputs with corresponding timer.
 */
void encoder_init_all(){
	encoder_init_tim1();
	encoder_init_tim2();
}

/**
 * @brief Read relative encoder movement since last poll.
 * @param[in] encoder index	0 to ENCODER_COUNT-1
 * @retval moved steps since last poll. (any poll)
 */
int32_t read_relative(uint8_t enc){
	if(enc < ENCODER_COUNT){
		int32_t t = encoder[enc]();
		return t;
	}
	return 0;
}

/**
 * @brief Read absolute encoder position since reset_absolute().
 * @param[in] encoder	index 0 to ENCODER_COUNT-1
 * @retval moved steps since last poll. (any poll)
 */
int32_t read_absolute(uint8_t enc){
	if(enc < ENCODER_COUNT){
		(void)lastPoll;
	}
	return 0;
}

/**
 * @brief Reset absolute encoder position.
 * @param[in] encoder	index 0 to ENCODER_COUNT-1
 */
void reset_absolute(uint8_t enc){
	if(enc < ENCODER_COUNT){
		
	}
}
/**
 * @}
 */
