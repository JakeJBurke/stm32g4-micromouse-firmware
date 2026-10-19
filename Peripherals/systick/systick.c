#include "systick.h"
#include "stm32g474xx.h"

#include <stddef.h>
#include <stdint.h>

#define SYSTICK_MAX_TICKS (1UL << 24)

static volatile uint32_t systick_elapsed_ms = 0;
static uint32_t systick_period_ms = 0;
static volatile uint8_t systick_initialized = 0;

SYSTICK_Status_t systick_init(SYSTICK_Config_t *cfg)
{
	if (cfg == NULL) return SYSTICK_ERR_INVALID_CONFIG;
	if (cfg->clock_hz == 0U) return SYSTICK_ERR_INVALID_CONFIG;
	if (cfg->timebase != SYSTICK_TIMEBASE_1MS && cfg->timebase != SYSTICK_TIMEBASE_10MS) return SYSTICK_ERR_INVALID_CONFIG;

	uint32_t interrupt_hz = (uint32_t)cfg->timebase;
	if (cfg->clock_hz % interrupt_hz != 0U) return SYSTICK_ERR_INVALID_CONFIG;

	uint32_t ticks = cfg->clock_hz / interrupt_hz;
	if (ticks == 0U || ticks > SYSTICK_MAX_TICKS) return SYSTICK_ERR_RELOAD;

	SysTick->CTRL = 0; // Disable SysTick when configuring

	SysTick->LOAD = ticks - 1U; // Set reload value

	SysTick->VAL = 0; // Clear current value

	// Reset software tracking values
	systick_elapsed_ms = 0;
	systick_period_ms = 1000U / interrupt_hz;

	// Enable counter, clock source, interrupt, and enable
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

	systick_initialized = 1U;

	return SYSTICK_OK;
}

void SysTick_Handler(void)
{
	systick_elapsed_ms += systick_period_ms;
}

uint32_t systick_get_ms(void)
{
	return systick_elapsed_ms;
}

uint32_t systick_get_s(void)
{
	return systick_get_ms() / 1000U;
}

SYSTICK_Status_t systick_delay_ms(uint32_t ms)
{
	if (!systick_initialized) return SYSTICK_ERR_NOT_INITIALIZED;

	uint32_t start = systick_get_ms();

	while ((uint32_t)(systick_get_ms() - start) < ms)
	{

		__NOP();
	}

	return SYSTICK_OK;
}

SYSTICK_Status_t systick_delay_s(uint32_t s)
{
	if (!systick_initialized) return SYSTICK_ERR_NOT_INITIALIZED;

	if (s > UINT32_MAX / 1000U) return SYSTICK_ERR;

	return systick_delay_ms(s * 1000U);
}
