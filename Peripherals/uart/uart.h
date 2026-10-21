#pragma once

#include <stdint.h>
#include "stm32g474xx.h"
#include "gpio/gpio.h"

typedef enum {
	UART_OK,
	UART_ERR
} UART_Status_t;

typedef struct {
	USART_TypeDef *instance;	// Which USART
	uint32_t clock_hz;			// clock speed
	uint32_t baud;				// set baud
	GPIO_Pin_t tx;				// tx port + pin
	GPIO_Pin_t rx;				// rx port + pin
	GPIO_AF_t alternate;		// Af number connection
} UART_Config_t;

UART_Status_t uart_init(UART_Config_t *cfg);

UART_Status_t uart_write_byte(USART_TypeDef *usart, uint8_t data);

UART_Status_t uart_write(USART_TypeDef *usart, const uint8_t *data, uint32_t len);

UART_Status_t uart_read_byte(USART_TypeDef *usart, uint8_t *data);
