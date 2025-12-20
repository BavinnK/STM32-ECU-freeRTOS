#include <MyRelay.h>

void relay_init(void) {
	RCC->AHB1ENR |= (1 << 1); //ENABLE GPIOB clock
	//the plan is to set the LOW RELAY to PB10, MID RELAY to PB5, HIGH RELAY to PB4

	// Clear MODER bits for PB10, PB5, PB4
	GPIOB->MODER &= ~((3 << 20) |   // PB10
			(3 << 10) |   // PB5
			(3 << 8)      // PB4
	);

	// Set OUTPUT mode (01)
	GPIOB->MODER |= ((1 << 20) |   // PB10
					 (1 << 10) |   // PB5
					 (1 << 8));      // PB4

	GPIOB->OTYPER &= ~((1 << 10) |
					   (1 << 5)  |
					   (1 << 4)  );
	GPIOB->OTYPER |= ((1 << 10) |
					  (1 << 5)  |
					  (1 << 4)  );
	GPIOB->PUPDR &= ~((0b11 << 2 * 10) |
					  (0b11 << 2 * 5)  |
					  (0b11 << 2 * 4)  );

	// ACTIVE-LOW relays → drive HIGH to keep them OFF at startup
	GPIOB->BSRR = (1 << 10) | (1 << 5) | (1 << 4);
}

void relay_set_fan_speed(FanSpeed_t speed) {
	switch (speed) {

	case FAN_SPEED_OFF:	//all relays OFF (PB10 HIGH, PB5 HIGH, PB4 HIGH)
		GPIOB->BSRR = (1 << 10) | (1 << 5) | (1 << 4);
		break;

	case FAN_SPEED_LOW:	//PB10 LOW (ON), PB5 HIGH (OFF), PB4 HIGH (OFF)
		GPIOB->BSRR = (1 << (10 + 16)) | (1 << 5) | (1 << 4);
		break;

	case FAN_SPEED_MEDIUM:	//PB5 LOW (ON), PB10 HIGH (OFF), PB4 HIGH (OFF)
		GPIOB->BSRR = (1 << (5 + 16)) | (1 << 10) | (1 << 4);
		break;

	case FAN_SPEED_HIGH:	//PB4 LOW (ON), PB10 HIGH (OFF), PB5 HIGH (OFF)
		GPIOB->BSRR = (1 << (4 + 16)) | (1 << 10) | (1 << 5);
		break;
	}
}
