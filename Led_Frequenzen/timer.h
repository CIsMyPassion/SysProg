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

static Timer_Handler timer0_handler;
static Timer_Handler timer1_handler;

typedef enum
{
	TIMER_PRESCALER_0 = 1,
	TIMER_PRESCALER_8 = 3,
	TIMER_PRESCALER_64 = 6,
	TIMER_PRESCALER_256 = 8,
	TIMER_PRESCALER_1024 = 10
} Timer_Prescaler;

static Timer_Prescaler timer0_prescaler;
static Timer_Prescaler timer1_prescaler;

void timer0_set_ocrn_frequency(uint16_t frequency)
{
	OCR0A = (((uint32_t) F_CPU >> timer0_prescaler) / frequency) - 1;
}

void timer1_set_ocrn_frequency(uint16_t frequency)
{
	OCR1A = (((uint32_t)F_CPU >> timer1_prescaler) / frequency) - 1;
}

void timer1_set_ocrn_seconds(uint16_t seconds)
{
	OCR1A = (((uint32_t)F_CPU >> timer1_prescaler) * seconds) - 1;
}

void timer0_init(Timer_Prescaler prescaler, uint16_t frequency, Timer_Handler handler)
{
	timer0_prescaler = prescaler;
	timer0_handler = handler;
	
	set_bit_for_port(&TCCR0A, WGM01); // Set CTC mode
	
	timer0_set_ocrn_frequency(frequency);
	
	switch (prescaler) // Set CSxx bits according to the prescaler
	{
		case TIMER_PRESCALER_0:
		set_bit_for_port(&TCCR0B, CS00);
		break;
		case TIMER_PRESCALER_8:
		set_bit_for_port(&TCCR0B, CS01);
		break;
		case TIMER_PRESCALER_64:
		set_bits_for_port(&TCCR0B, (1 << CS01) | (1 << CS00));
		break;
		case TIMER_PRESCALER_256:
		set_bit_for_port(&TCCR0B, CS02);
		break;
		case TIMER_PRESCALER_1024:
		set_bits_for_port(&TCCR0B, (1 << CS02) | (1 << CS00));
		break;
	}
	
	set_bit_for_port(&TIMSK0, OCIE0A); // Set timer counter interrupt mask to enable interrupt from timer 0
}

void timer1_init(Timer_Prescaler prescaler, uint16_t time, uint8_t as_seconds, Timer_Handler handler)
{
	timer1_prescaler = prescaler;
	timer1_handler = handler;
	
	set_bit_for_port(&TCCR1B, WGM12); // Set CTC mode
	
	if (as_seconds)
	{
		timer1_set_ocrn_seconds(time);
	}
	else
	{
		timer1_set_ocrn_frequency(time);
	}
	//OCR1A = 0x3D05;
	
	switch (prescaler) // Set CSxx bits according to the prescaler
	{
		case TIMER_PRESCALER_0:
		set_bit_for_port(&TCCR1B, CS10);
		break;
		case TIMER_PRESCALER_8:
		set_bit_for_port(&TCCR1B, CS11);
		break;
		case TIMER_PRESCALER_64:
		set_bits_for_port(&TCCR1B, (1 << CS11) | (1 << CS10));
		break;
		case TIMER_PRESCALER_256:
		set_bit_for_port(&TCCR1B, CS12);
		break;
		case TIMER_PRESCALER_1024:
		set_bits_for_port(&TCCR1B, (1 << CS12) | (1 << CS10));
		break;
	}
	
	set_bit_for_port(&TIMSK1, OCIE1A); // Set timer counter interrupt mask to enable interrupt from timer 1
}

ISR(TIMER0_COMPA_vect)
{
	timer0_handler(); // Execute timer interrupt handler
}

ISR(TIMER1_COMPA_vect)
{
	timer1_handler(); // Execute timer interrupt handler
}

#endif /* TIMER_OPERATIONS_H_ */