#include "app.h"

#include "app_config.h"
#include "device_instances.h"

#include "systick/systick.h"
#include "led/led.h"

static uint32_t previous_toggle_ms;

void app_init(void)
{
	previous_toggle_ms = systick_get_ms();
}

void app_update(void)
{
	uint32_t current_ms = systick_get_ms();

	if (current_ms - previous_toggle_ms >= APP_STATUS_LED_PERIOD_MS)
	{
		previous_toggle_ms = current_ms;
		led_toggle(board_get_status_led());
	}
}
