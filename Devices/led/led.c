#include "led.h"
#include <stddef.h>

LED_Status_t led_init(LED_t *led)
{
	if (led == NULL) return LED_ERR;

	GPIO_Config_t cfg = {
		.port = led->port,
		.pin = led->pin,
		.mode = GPIO_MODE_OUTPUT,
		.otype = GPIO_PUSH_PULL,
		.speed = GPIO_SPEED_HIGH,
		.pull = GPIO_NO_PULL,
		.alternate = GPIO_AF0
	};
	if (gpio_init(&cfg) != GPIO_OK) return LED_ERR;

	return LED_OK;
}

LED_Status_t led_toggle(LED_t *led)
{
	if (led == NULL) return LED_ERR;

	GPIO_Pin_t gpio = {
		.port = led->port,
		.pin = led->pin
	};

	if (gpio_toggle(&gpio) != GPIO_OK) return LED_ERR;

	return LED_OK;
}

LED_Status_t led_on(LED_t *led)
{
	if (led == NULL) return LED_ERR;

	GPIO_Pin_t gpio = {
		.port = led->port,
		.pin = led->pin
	};

	if (gpio_write(&gpio, GPIO_HIGH) != GPIO_OK) return LED_ERR;

	return LED_OK;
}

LED_Status_t led_off(LED_t *led)
{
	if (led == NULL) return LED_ERR;

	GPIO_Pin_t gpio = {
		.port = led->port,
		.pin = led->pin
	};

	if (gpio_write(&gpio, GPIO_LOW) != GPIO_OK) return LED_ERR;

	return LED_OK;
}
