#include "board_init.h"

#include <stdint.h>
#include <stddef.h>

#include "board_config.h"
#include "device_instances.h"

#include "systick/systick.h"

#include "led/led.h"

BOARD_Status_t board_init(void)
{
	LED_t *status_led = board_get_status_led();
	if (status_led == NULL) return BOARD_STATUS_LED_ERROR;

	SYSTICK_Config_t systick_cfg = {
		.clock_hz = BOARD_FCLK_HZ,
		.timebase = SYSTICK_TIMEBASE_1MS
	};

	if (systick_init(&systick_cfg) != SYSTICK_OK) return BOARD_STATUS_SYSTICK_ERROR;

	if (led_init(status_led) != LED_OK) return BOARD_STATUS_LED_ERROR;

	return BOARD_STATUS_OK;
}
