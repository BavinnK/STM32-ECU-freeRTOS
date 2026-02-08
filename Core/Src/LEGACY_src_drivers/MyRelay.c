#include <MyRelay.h>

void relay_init(void) {
	RCC->AHB1ENR |= (1 << 1); //ENABLE GPIOB clock
	//the plan is to set the LOW RELAY to PB3, MID RELAY to PB5, HIGH RELAY to PB4

	// Clear MODER bits for PB3, PB5, PB4
	GPIOB->MODER &= ~((3 << (3*2)) |   // PB3
			(3 << 10) |   // PB5
			(3 << 8)      // PB4
	);

	// Set OUTPUT mode (01)
	GPIOB->MODER |= ((1 << (3*2)) |   // PB3
					 (1 << 10) |   // PB5
					 (1 << 8));      // PB4

	GPIOB->OTYPER &= ~((1 << 3) |
					   (1 << 5)  |
					   (1 << 4)  );
	GPIOB->OTYPER |= ((1 << 3) |
					  (1 << 5)  |
					  (1 << 4)  );
	GPIOB->PUPDR &= ~((0b11 << 2 * 3) |
					  (0b11 << 2 * 5)  |
					  (0b11 << 2 * 4)  );

	// ACTIVE-LOW relays → drive HIGH to keep them OFF at startup
	GPIOB->BSRR = (1 << 3) | (1 << 5) | (1 << 4);
}

void relay_set_fan_speed(FanSpeed_t speed) {
	switch (speed) {

	case FAN_SPEED_OFF:	//all relays OFF (PB3 HIGH, PB5 HIGH, PB4 HIGH)
		GPIOB->BSRR = (1 << 3) | (1 << 5) | (1 << 4);
		break;

	case FAN_SPEED_LOW:	//PB3 LOW (ON), PB5 HIGH (OFF), PB4 HIGH (OFF)
		GPIOB->BSRR = (1 << (3 + 16)) | (1 << 5) | (1 << 4);
		break;

	case FAN_SPEED_MEDIUM:	//PB5 LOW (ON), PB3 HIGH (OFF), PB4 HIGH (OFF)
		GPIOB->BSRR = (1 << (5 + 16)) | (1 << 3) | (1 << 4);
		break;

	case FAN_SPEED_HIGH:	//PB4 LOW (ON), PB3 HIGH (OFF), PB5 HIGH (OFF)
		GPIOB->BSRR = (1 << (4 + 16)) | (1 << 3) | (1 << 5);
		break;
	}
}
