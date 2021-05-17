/*
 * timer_operations.h
 *
 * Created: 16.05.2021 12:07:58
 *  Author: Jannis Kruse
 */ 

#ifndef TIMER_OPERATIONS_H_
#define TIMER_OPERATIONS_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/interrupt.h>
#include "port_operations.h"

typedef void (* Timer_Handler)();
Timer_Handler timer_handler;

static uint16_t timer_prescaler;

void timer_set_ocrn(uint16_t frequency)
{
	OCR0A = (((uint32_t)F_CPU / timer_prescaler) / frequency) - 1;
}

void timer_init(uint16_t prescaler, uint16_t frequency, Timer_Handler handler)
{
	timer_prescaler = prescaler;
	timer_handler = handler;
	timer_set_ocrn(frequency);
	
	TCCR0A |= (1 << WGM01);
	
	switch (prescaler)
	{
		case 8:
			set_bit_for_port(&TCCR0B, (1 << CS01));
			break;
		case 64:
			set_bit_for_port(&TCCR0B, (1 << CS01) | (1 << CS00));
			break;
		case 256:
			set_bit_for_port(&TCCR0B, (1 << CS02));
			break;
		case 1024:
			set_bit_for_port(&TCCR0B, (1 << CS02) | (1 << CS00));
			break;
	}
	
	TIMSK0 |= (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	timer_handler(); // Execute timer interrupt handler
}

#endif /* TIMER_OPERATIONS_H_ */