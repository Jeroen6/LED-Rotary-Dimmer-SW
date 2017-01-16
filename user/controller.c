/**
  ******************************************************************************
  * @file    	controller.c
  * @author  	JLO
  * @version 	V1.0.0
  * @date		 	June 2016
  * @brief   	LED Controller state machine.
	*
	* @detail  	
	*
	* @note			Yes, this is a complicated implementation of a state machine.
	*					 
  ******************************************************************************
	* @{
  */
/* Includes ------------------------------------------------------------------*/
#include "controller.h"

/* Settings ------------------------------------------------------------------*/

/* Interrupt shared variables ------------------------------------------------*/

/* Public --------------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables (static forbids external use) ---------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief LED Controller statemachine states
 * @addtogroup States LED Controller
 * @{
 */
static void* s00_entry							(Ctrl_t *p);
static void* s00_normal_disabled		(Ctrl_t *p);
static void* s01_normal_rampup			(Ctrl_t *p);
static void* s02_normal_enabled			(Ctrl_t *p);
static void* s03_normal_rampdown		(Ctrl_t *p);
static void* s10_config_entry				(Ctrl_t *p);
static void* s11_config_minlevel		(Ctrl_t *p);
static void* s12_config_maxlevel		(Ctrl_t *p);
static void* s13_config_rampup			(Ctrl_t *p);
static void* s14_config_rampdown		(Ctrl_t *p);
/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/** 
 * @brief Initialize a controller instance.
 * @param[in] pointer to instance
 */
void controller_init(Ctrl_t *p){
	p->cstate = s00_entry;
	p->pstate = NULL;
}

/** 
 * @brief Execute controller instance
 * @param[in] pointer to instance
 */
void controller_execute(Ctrl_t *p){
	state_t exc = (state_t)p->cstate;
	if( exc != NULL ){
		p->pstate = p->cstate;
		p->cstate = (state_t)exc(p);
	}
}

/** 
 * @brief Entry state.
 * @detail Check previous channel setting and resume operation.
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s00_entry(Ctrl_t *p){
	return s00_entry;
}
/** 
 * @brief Channel Off operation.
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s00_normal_disabled(Ctrl_t* pstate){
	return s00_normal_disabled;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s01_normal_rampup(Ctrl_t *p){
	return s01_normal_rampup;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s02_normal_enabled(Ctrl_t *p){
	return s02_normal_enabled;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s03_normal_rampdown(Ctrl_t *p){
	return s03_normal_rampdown;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s10_config_entry(Ctrl_t *p){
	return s10_config_entry;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s11_config_minlevel(Ctrl_t *p){
	return s11_config_minlevel;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s12_config_maxlevel(Ctrl_t *p){
	return s12_config_maxlevel;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s13_config_rampup(Ctrl_t *p){
	return s13_config_rampup;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
static void* s14_config_rampdown(Ctrl_t *p){
	return s14_config_rampdown;
}
/** 
 * @brief 
 * @param[in] pointer to previous state
 * @return pointer to next state
 */
/**
 * @}
 */
