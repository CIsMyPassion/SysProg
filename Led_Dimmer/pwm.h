/*
 * pwm.h
 *
 * Created: 17/05/2021 18:54:01
 *  Author: sjno
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

inline void pwm_set_duty_cycle(uint8_t duty)
{
	set_port(&OCR0A, duty);
}

inline void pwm_init()
{
	set_port(&DDRD, (1 << DDD6));
	pwm_set_duty_cycle(128);

	uint8_t tccr0a_byte = (1 << COM0A1)	// none-inverting mode
				| (1 << WGM01)
				| (1 << WGM00);		// fast PWM Mode
	set_port(&TCCR0A, tccr0a_byte);
	
	set_port(&TCCR0B, (1 << CS01));		// set prescaler to 8 and starts PWM
}

#endif /* PWM_H_ */