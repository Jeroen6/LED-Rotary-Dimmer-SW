/**
  ******************************************************************************
  * @file    Interrupts.c
  * @author  JLO
  * @version V1.0.0
  * @date    May 2016
  * @brief   Consolidated file for interrupts forwarding, 
	*          as some interrupts are shared.
	* @detail  
	*					 
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "interrupts.h"
#include "memories.h"

/* Settings ------------------------------------------------------------------*/
/* Public --------------------------------------------------------------------*/
volatile uint32_t systime;
/* Persistent public ---------------------------------------------------------*/
volatile int exitCode;	/// Persistent var used to indicate previous exitcode;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables (static forbids external use) ---------------------------*/
/* Private functions ---------------------------------------------------------*/

/** 
 * @brief	Copy the vector table to SRAM and remap. This reduces random access events from flash.
 * @details This requires an 0x100 offset for the linker IRAM1 base: 0x20000100 size: 0x3F00
 **/
void IT_RemapVectorTable(void){
	uint16_t i;
	uint32_t *flashVectorTable = (void*)flash_full.base;
	uint32_t *sramVectorTable = (void*)sram_main.base;
	
	for(i=0; i<0x100; i++){
		*sramVectorTable++ = *flashVectorTable++;
	}
  // Remap RAM into 0x0000 0000
	__disable_irq();
  __HAL_SYSCFG_REMAPMEMORY_SRAM();
	__enable_irq();
}

/** 
 * @brief	Non Maskable Interrupt
 * @details A Non Maskable Interrupt (NMI) can be signalled by a peripheral or triggered by software. 
 *          This is the highest priority exception other than reset. It is permanently enabled and has a fixed priority of -2. NMIs cannot be:
 *          masked or prevented from activation by any other exception
 *          preempted by any exception other than Reset.
 **/
void NMI_Handler(void){
	__NOP();
}

/** 
 * @brief	Critical error, reset system or on debugger
 **/
void HardFault_Handler(void){
	// Only set when not already set. 
	// Hardfault is a catch all without debugger for __BKTP()
	if( exitCode == 0 ) exitCode = IT_EXITCODE_HARDFAULT;
	__NOP();
	NVIC_SystemReset();
}

/** 
 * @brief	Supervisor call (SVC).
 **/
void SVC_Handler(void){
	__NOP();
}

/**
 * @brief PendSV is an interrupt-driven request for system-level service.
 **/
void PendSV_Handler(void){
	__NOP();
}

/**
 * @brief SysTick timer interrupt. Used for system time at 1 ms resolution.
 **/
void SysTick_Handler(void){
	systime++;
}

/**
 * @brief	Unhandled interrupt vector. Not supposed to happen.
 **/
void Default_Handler_c(void){
	exitCode = IT_EXITCODE_UNHANDLED;
	__NOP();
	__BKPT(0);
}

/**
 * @brief
 **/
void WWDG_IRQHandler(void){
	exitCode = IT_EXITCODE_WWDG;
}

/**
 * @brief
 **/
void PVD_VDDIO2_IRQHandler(void){

}

/**
 * @brief
 **/
void RTC_IRQHandler(void){

}

/**
 * @brief
 **/
void FLASH_IRQHandler(void){

}

/**
 * @brief
 **/
void RCC_CRS_IRQHandler(void){

}

/**
 * @brief
 **/
void EXTI0_1_IRQHandler(void){

}

/**
 * @brief
 **/
void EXTI2_3_IRQHandler(void){

}

/**
 * @brief
 **/
void EXTI4_15_IRQHandler(void){

}

/**
 * @brief
 **/
void TSC_IRQHandler(void){

}

/**
 * @brief
 **/
void DMA1_Channel1_IRQHandler(void){

}

/**
 * @brief
 **/
void DMA1_Channel2_3_IRQHandler(void){

}

/**
 * @brief
 **/
void DMA1_Channel4_5_6_7_IRQHandler(void){

}

/**
 * @brief
 **/
void ADC1_COMP_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM1_BRK_UP_TRG_COM_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM1_CC_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM2_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM3_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM6_DAC_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM7_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM14_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM15_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM16_IRQHandler(void){

}

/**
 * @brief
 **/
void TIM17_IRQHandler(void){

}

/**
 * @brief
 **/
void I2C1_IRQHandler(void){

}

/**
 * @brief
 **/
void I2C2_IRQHandler(void){

}

/**
 * @brief
 **/
void SPI1_IRQHandler(void){

}

/**
 * @brief
 **/
void SPI2_IRQHandler(void){

}

/**
 * @brief
 **/
void USART1_IRQHandler(void){

}

/**
 * @brief
 **/
void USART2_IRQHandler(void){

}

/**
 * @brief
 **/
void USART3_4_IRQHandler(void){

}

/**
 * @brief
 **/
void CEC_CAN_IRQHandler(void){

}

/**
 * @brief
 **/
void USB_IRQHandler(void){

}
