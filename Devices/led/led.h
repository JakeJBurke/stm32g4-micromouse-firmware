#pragma once

#include "gpio/gpio.h"

typedef enum {
	LED_OK,
	LED_ERR
} LED_Status_t;

typedef struct {
	GPIO_TypeDef *port;
	uint8_t pin;
} LED_t;

LED_Status_t led_init(LED_t *led);

LED_Status_t led_toggle(LED_t *led);

LED_Status_t led_on(LED_t *led);

LED_Status_t led_off(LED_t *led);

LED_Status_t led_set_brightness(LED_t *led, uint32_t brightness);
