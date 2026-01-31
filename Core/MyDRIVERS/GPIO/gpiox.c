#include "../gpio/gpiox.h"

static inline void port_init(GPIO_TypeDef *ptr) {
	if (ptr == GPIOA)
		RCC->AHB1ENR |= (1 << 0);
	else if (ptr == GPIOB)
		RCC->AHB1ENR |= (1 << 1);
	else if (ptr == GPIOC)
		RCC->AHB1ENR |= (1 << 2);
}
void gpio_init(GPIO_TypeDef *port, gpio_set_up *ptr) {
	port_init(port);
	port->MODER &= ~((0b11) << (ptr->PINx * 2));
	port->MODER |= ((ptr->MODERx) << (ptr->PINx * 2));

	port->OTYPER &= ~((0b1) << (ptr->PINx));
	port->OTYPER |= ((ptr->OTYPERx) << (ptr->PINx));

	port->OSPEEDR &= ~((0b11) << (ptr->PINx * 2));
	port->OSPEEDR |= ((ptr->OSPEEDRx) << (ptr->PINx * 2));

	port->PUPDR &= ~((0b11) << (ptr->PINx * 2));
	port->PUPDR |= ((ptr->PUPDRx) << (ptr->PINx * 2));

}
void gpio_set(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1 << pin);
}

void gpio_reset(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1 << (pin + 16));
}
