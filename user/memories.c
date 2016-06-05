#include "stm32f0xx.h"
#include "memories.h"

//                   REGION             = { START     ,	SIZE       };
//const mem_region_t mem_example_region = { 0x00000000, 0x00008000 };
/// FLASH regions:
const mem_region_t flash_full  			= { 0x08000000, 0x20000 };	/// Flash sector 0 to 127, 128 Kbytes
const mem_region_t flash_sector0 		= { 0x08000000, 0x1000 };		/// Flash sector 0, 4 Kbytes
const mem_region_t flash_sector31		= { 0x0801F000, 0x1000 };		/// Flash sector 31, 4 Kbytes
const mem_region_t flash_system1 		= { 0x1FFFC800, 0x3000 };		///	System Memory, 12 kB.
const mem_region_t flash_system2 		= { 0x1FFFD800, 0x2000 };		///	System Memory, 8 kB.
const mem_region_t option_bytes 		= { 0x1FFFF800, 0xF };			///	Option bytes, 16 bytes.
// There are 31 flash sectors, each split in 2 pages.

/// SRAM regions:
const mem_region_t sram_main 				= { 0x20000000, 0x4000 };		/// SRAM1 Main SRAM, 16 Kbytes

/**
 * @brief   Validate a SRAM pointer
 * @return	Memory area
 * @retval	INVALID	0
 * @retval	MAIN		1
 * @retval	AUX			2
 * @retval	CCM			3
 * @retval	BACKUP	4
 */
int8_t mem_validate_ram(void *address){
	register uint32_t p = (uint32_t)address;
	if( p >= sram_main.base && p < sram_main.base + sram_main.size )
		return 1;
	return 0;
}

/**
 * @brief   Validate a FLASH pointer
 * @param[in] Any pointer
 * @return	Validation
 * @retval	INVALID	0
 * @retval	VALID		1
 */
int8_t mem_validate_flash(void *address){
	register uint32_t p = (uint32_t)address;
	if( p >= flash_full.base && p < flash_full.base + flash_full.size )
		return 1;
	if( p >= flash_system1.base && p < flash_system1.base + flash_system1.size )
		return 1;
	if( p >= flash_system2.base && p < flash_system2.base + flash_system2.size )
		return 1;
	return 0;
}

/**
 * @brief   Get the flash sector of given address
 * @return	Memory area
 * @retval	INVALID					-1
 * @retval	Flash Sector		n
 */
int16_t mem_flash_sector(void *address){
	if(mem_validate_flash(address)){
		register uint32_t p = (uint32_t)address;
		// Subtract flash base to get offset
		p -= flash_full.base;
		// Divide offset with sector size to get sector
		return p / flash_sector0.size;
	}else{
		// Not a flash pointer
		return -1;
	}
}

/**
 * @brief   Verify Flash integrity
 * @return	Success or failed
 * @retval	-1	Failed
 * @retval	1		Success
 * @retval	2		Written crc's, first run
 */
int8_t mem_flash_test(void){
#warning todo
	return 1;
}

/**
 * @brief   Rewrite the entire SRAM to calculate parities.
 */
void mem_initiate_parity(void){
	uint32_t *base = (void*)(sram_main.base);
	uint32_t *p = (void*)(sram_main.base + sram_main.size);
	while(p-- > base){ *p = *p; };
}
