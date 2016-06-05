#ifndef MEMORIES_H_
#define MEMORIES_H_

#include <inttypes.h>

typedef const struct {
	const uint32_t base;
	const uint32_t size;
} mem_region_t;

//                   REGION             = { START     ,	SIZE       };
//const mem_region_t mem_example_region = { 0x00000000, 0x00008000 };
extern const mem_region_t flash_full;
extern const mem_region_t flash_bank1;
extern const mem_region_t flash_bank2;
extern const mem_region_t flash_sector0;
extern const mem_region_t flash_sector31;
extern const mem_region_t flash_sector32;
extern const mem_region_t flash_sector127;
extern const mem_region_t flash_system1;
extern const mem_region_t flash_system2;
extern const mem_region_t option_bytes;

extern const mem_region_t sram_main;

extern uint32_t mem_crc_bank1;
extern uint32_t mem_crc_bank2;

/// Calculate flash sector base
#define flash_sector_base(sector)			((sector<512)?(flash_full.base + (0x800u*sector)):(-1))
/// Calculate flash sector seize
#define flash_sector_size(sector)			(0x800u)

int8_t mem_validate_ram(void *address);
int8_t mem_validate_flash(void *address);
int16_t mem_flash_sector(void *address);
int8_t mem_flash_test(void);
void mem_initiate_parity(void);

#define UNIQUE_ID1  (*(uint32_t *)0x1FFFF7E8)
#define UNIQUE_ID2	(*(uint32_t *)0x1FFFF7EC)
#define UNIQUE_ID3	(*(uint32_t *)0x1FFFF7F0)

#endif //MEMORIES_H_
