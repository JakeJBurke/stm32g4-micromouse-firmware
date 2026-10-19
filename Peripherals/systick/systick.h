#pragma once

#include <stdint.h>

typedef enum {
	SYSTICK_OK,
	SYSTICK_ERR_INVALID_CONFIG,
	SYSTICK_ERR_RELOAD,
	SYSTICK_ERR_NOT_INITIALIZED,
	SYSTICK_ERR
} SYSTICK_Status_t;

typedef enum {
	SYSTICK_TIMEBASE_1MS = 1000U,
	SYSTICK_TIMEBASE_10MS = 100U
} SYSTICK_Timebase_t;

typedef struct {
	uint32_t clock_hz;
	SYSTICK_Timebase_t timebase;
} SYSTICK_Config_t;

SYSTICK_Status_t systick_init(SYSTICK_Config_t *cfg);

SYSTICK_Status_t systick_delay_ms(uint32_t ms);

SYSTICK_Status_t systick_delay_s(uint32_t s);

uint32_t systick_get_ms(void);

uint32_t systick_get_s(void);
