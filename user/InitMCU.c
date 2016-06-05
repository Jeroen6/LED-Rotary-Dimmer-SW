/**
  ******************************************************************************
  * @file    InitMCU.c
  * @author  JLO
  * @version V1.0.0
  * @date    February 2015
  * @brief   Initialize the core functionality of the MCU.
	*
	* @detail  
	*					 
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "InitMCU.h"
#include "interrupts.h"
#include <string.h>

/* Settings ------------------------------------------------------------------*/
/**
 * @brief Normal use oscillator configuration.
 * @details Run from HSI, with LSI for IWDG.
 */
const RCC_OscInitTypeDef RCC_INIT_OSC_Final = {
	/* OscillatorType	       */  0, 
	/* HSEState              */  RCC_HSE_OFF, 
	/* LSEState              */  RCC_LSE_OFF, 
	/* HSIState              */  RCC_HSI_ON, 
	/* HSICalibrationValue   */  RCC_HSICALIBRATION_DEFAULT, 
	/* HSI14State            */  RCC_HSI14_OFF, 
	/* HSI14CalibrationValue */  RCC_HSI14CALIBRATION_DEFAULT, 
	/* HSI48State            */  RCC_HSI48_OFF, 
	/* LSIState              */  RCC_LSI_ON,
	{
		/* PLLState  */ RCC_PLL_OFF,
		/* PLLSource */ RCC_PLLSOURCE_HSI,
		/* PLLMUL    */ RCC_PLL_MUL12,
		/* PREDIV    */ RCC_PREDIV_DIV1
	}
};

/**
 * @brief Normal use clock tree configuration.
 * @details Run from HSI.
 */
const RCC_ClkInitTypeDef RCC_ClkInit_Final = {
	/* ClockType      */ RCC_CLOCKTYPE_SYSCLK | 
											 RCC_CLOCKTYPE_HCLK | 
											 RCC_CLOCKTYPE_PCLK1,
	/* SYSCLKSource   */ RCC_SYSCLKSOURCE_HSI,
	/* AHBCLKDivider  */ RCC_SYSCLK_DIV1,
	/* APB1CLKDivider */ RCC_HCLK_DIV1
};

/**
 * @brief GPIOA init table.
 * @note It is possible to compress this table using OR on the GPIO_PIN_x value.
 */
const GPIO_InitTypeDef GPIOA_Init[] = {
/* pin, mode, pull, speed, alternate */
	{GPIO_PIN_0, /* nc 					*/ GPIO_MODE_INPUT,    	GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_1, /* NTC 				*/ GPIO_MODE_ANALOG,    GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_2, /* PWM_CH1 		*/ GPIO_MODE_AF_PP,    	GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF0_TIM15},
	{GPIO_PIN_3, /* PWM_CH2 		*/ GPIO_MODE_AF_PP,    	GPIO_NOPULL, 		GPIO_SPEED_FREQ_LOW, GPIO_AF0_TIM15},
	{GPIO_PIN_4, /* nc 					*/ GPIO_MODE_INPUT,    	GPIO_PULLDOWN, 	GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_5, /* nc 					*/ GPIO_MODE_INPUT,    	GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_6, /* BEEP 				*/ GPIO_MODE_AF_PP,    	GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF5_TIM16},
	{GPIO_PIN_7, /* ENC1_GREEN 	*/ GPIO_MODE_AF_PP, 		GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, GPIO_AF1_TIM3},
	{GPIO_PIN_8, /* ENC1_A 			*/ GPIO_MODE_INPUT, 		GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM1},
	{GPIO_PIN_9, /* ENC1_C 			*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN, 	GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM1},
	{GPIO_PIN_10,/* ENC1_SW 		*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_11,/* nc 					*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_12,/* ENC2_SW 		*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_13,/* SWDIO 			*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_14,/* SWDCLK 			*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_15,/* ECN2_A 			*/ GPIO_MODE_INPUT,     GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM2},
};

/**
 * @brief GPIOB init table.
 * @note It is possible to compress this table using OR on the GPIO_PIN_x value.
 */
const GPIO_InitTypeDef GPIOB_Init[] = {
/* pin, mode, pull, speed, alternate */
	{GPIO_PIN_0,  /* ENC2_RED 	*/ GPIO_MODE_AF_PP, 		GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF1_TIM3},
	{GPIO_PIN_1,  /* ENC2_GREEN */ GPIO_MODE_AF_PP,   	GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF1_TIM3},
	{GPIO_PIN_3,  /* ENC2_C 		*/ GPIO_MODE_INPUT,   	GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, GPIO_AF2_TIM2},
	{GPIO_PIN_4,  /* ENC1_RED 	*/ GPIO_MODE_AF_PP, 		GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF1_TIM3},
	{GPIO_PIN_5,  /* MEM_WC			*/ GPIO_MODE_INPUT, 		GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW, 0},
	{GPIO_PIN_6,  /* I2C_SCL 		*/ GPIO_MODE_AF_PP,     GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF1_I2C1},
	{GPIO_PIN_7,  /* I2C_SDA 		*/ GPIO_MODE_AF_PP,     GPIO_NOPULL,   	GPIO_SPEED_FREQ_LOW, GPIO_AF1_I2C1},
};

/**
 * @brief IWDG configuration handle.
 * @note Must be in RW Region. Contains init and status.
 */
IWDG_HandleTypeDef IWDG_handle = {
	/* Instance 	*/	IWDG,              
	{	
	/* Prescaler 	*/	IWDG_PRESCALER_4,	// source 40khz
  /* Reload 		*/	10000,						// source 10khz
  /* Window 		*/	0
	},
	{
	/* HAL Locked	*/	HAL_UNLOCKED
	},
	{
	/* State 			*/	HAL_IWDG_STATE_RESET
	}
};

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ----------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Check boot source and previous error.
	* @retval -1 on safemode boot.  
	* @retval 0 on normal boot.
  * @retval 1 on special boot.
  */
int BootCheck(void){
	// Read reset flags.
	uint32_t resetSource = RCC->CSR;
	// Clear reset flags.
	RCC->CSR |= RCC_FLAG_RMV;
	// Read resetsource to set exitCode accordingly.
	if( resetSource & RCC_FLAG_PINRST ){
		__NOP(); // Cold boot
	}
	if( resetSource & RCC_FLAG_PORRST ){
		__NOP(); // Cold boot
	}
	if( resetSource & RCC_FLAG_LPWRRST){
		__NOP();
	}
	if( resetSource & RCC_FLAG_SFTRST  || 
			resetSource & RCC_FLAG_IWDGRST ||
			resetSource & RCC_FLAG_WWDGRST ){
		// On watchddog or software reset.
		if(exitCode == 0){
			if(resetSource & RCC_FLAG_IWDGRST){
				exitCode = IT_EXITCODE_IWDG;
			}
		}
	}
 
	if(exitCode == 0){
		// Hot reset requested by code.
		__NOP();
	}
	if(exitCode == IT_EXITCODE_HARDFAULT){
		// Hot reset due to hardfault
		__NOP();
	}
	if(exitCode == IT_EXITCODE_UNHANDLED){
		// Hot reset due to unhandled interrupt
		__NOP();
	}
	if(exitCode == IT_EXITCODE_WWDG){
		// Hot reset due to unhandled interrupt
		__NOP();
	}
	if(exitCode == IT_EXITCODE_WWDG){
		// Hot reset due to unhandled interrupt
		__NOP();
	}
	// Clear exitcode
	exitCode = IT_EXITCODE_NORMAL;
	return 0;
}

/**
  * @brief  Setup clock tree and core functionality.
  * @retval -1 on failure.
  */
int InitMCU(void){	
	RCC_OscInitTypeDef rcc_init_osc;
	RCC_ClkInitTypeDef rcc_clkinit;
	// Load settings to ram
	memcpy( &rcc_init_osc, &RCC_INIT_OSC_Final, sizeof(RCC_INIT_OSC_Final));
	memcpy( &rcc_clkinit, &RCC_ClkInit_Final, sizeof(RCC_ClkInitTypeDef));
	
	//1. Initialize clock tree.
	HAL_Init();
	// Run on all unused clk's.
	rcc_init_osc.OscillatorType = RCC_OSCILLATORTYPE_HSE |
                                RCC_OSCILLATORTYPE_LSE | 
                                RCC_OSCILLATORTYPE_LSI |  
                                RCC_OSCILLATORTYPE_HSI14;
	HAL_RCC_OscConfig(&rcc_init_osc);
	// Setup clk tree.
	HAL_RCC_ClockConfig(&rcc_clkinit, FLASH_LATENCY_1);
	// Disable clk that was used last before.
	rcc_init_osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	HAL_RCC_OscConfig(&rcc_init_osc);	
	
	//2. Verify clock tree.
	#warning TODO
	
	//3. Enable core peripherals.
	HAL_PWR_EnableBkUpAccess();
	//RCC_AHB_Clock_Enable_Disable
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_SRAM_CLK_ENABLE();
	__HAL_RCC_FLITF_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_ADC1_CLK_ENABLE();		// NTC input
	__HAL_RCC_TIM1_CLK_ENABLE();		// Encoder input
	__HAL_RCC_TIM2_CLK_ENABLE();		// Encoder input
	__HAL_RCC_TIM3_CLK_ENABLE();		// Encoder LED outputs pwm x4
	__HAL_RCC_TIM15_CLK_ENABLE();		// PWM channel outputs
	__HAL_RCC_TIM16_CLK_ENABLE();		// Beep
	__HAL_RCC_DBGMCU_CLK_ENABLE();
	
	//4. Remap vector table to RAM for faster lookup.
	IT_RemapVectorTable();
	
	//5. Enable IWDG
	HAL_IWDG_Init(&IWDG_handle);
	HAL_IWDG_Start(&IWDG_handle);
	
	return 0;
}

/**
  * @brief  Setup gpio.
  * @retval -1 on failure.
  */
int InitGPIO(void){
	uint16_t i;
	for(i=0; i<16; i++){HAL_GPIO_Init(GPIOA, (GPIO_InitTypeDef*)&GPIOA_Init);	}
	for(i=0; i<7; i++){HAL_GPIO_Init(GPIOB, (GPIO_InitTypeDef*)&GPIOB_Init);	}
	return 0;
}
