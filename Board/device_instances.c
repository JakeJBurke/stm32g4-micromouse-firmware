#include "device_instances.h"

static LED_t status_led = {
	.port = GPIOC,
	.pin = 6,
};

LED_t* board_get_status_led(void)
{
	return &status_led;
}
