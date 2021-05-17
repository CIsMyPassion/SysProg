/*
 * Lauf_Led.c
 *
 * Created: 12/05/2021 23:26:31
 * Author : sjno
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#include "port_operations.h"
#include "timer.h"

volatile int lookup_index = 0;

const uint8_t lookup_table[] = {
	(1 << PORTB5) | (1 << PORTB0), // [ 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 ]
	(1 << PORTB5) | (1 << PORTB1), // [ 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 ]
	(1 << PORTB5) | (1 << PORTB2), // [ 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 ]
	(1 << PORTB5) | (1 << PORTB3), // [ 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 ]
	(1 << PORTB4) | (1 << PORTB0), // [ 0 | 0 | 0 | 1 | 0 | 0 | 0 | 1 ]
	(1 << PORTB4) | (1 << PORTB1), // [ 0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 ]
	(1 << PORTB4) | (1 << PORTB2), // [ 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 ]
	(1 << PORTB4) | (1 << PORTB3), // [ 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 ]
	(1 << PORTB4) | (1 << PORTB3), // [ 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 ]
	(1 << PORTB4) | (1 << PORTB2), // [ 0 | 0 | 0 | 1 | 0 | 1 | 0 | 0 ]
	(1 << PORTB4) | (1 << PORTB1), // [ 0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 ]
	(1 << PORTB4) | (1 << PORTB0), // [ 0 | 0 | 0 | 1 | 0 | 0 | 0 | 1 ]
	(1 << PORTB5) | (1 << PORTB3), // [ 0 | 0 | 1 | 0 | 1 | 0 | 0 | 0 ]
	(1 << PORTB5) | (1 << PORTB2), // [ 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 ]
	(1 << PORTB5) | (1 << PORTB1), // [ 0 | 0 | 1 | 0 | 0 | 0 | 1 | 0 ]
	(1 << PORTB5) | (1 << PORTB0)  // [ 0 | 0 | 1 | 0 | 0 | 0 | 0 | 1 ]
};

void switch_to_next_led_handler()
{
	set_port(&PORTB, lookup_table[lookup_index++ % 16]);
}

inline void configure_leds()
{
	const uint8_t ddrb_byte = (1 << DDB0) | (1 << DDB1)
				| (1 << DDB2) | (1 << DDB3)
				| (1 << DDB4) | (1 << DDB5);
	
	set_port(&DDRB, ddrb_byte);
	set_port(&PORTB, *lookup_table);
}

inline void init()
{
	uint16_t time_in_seconds = 1;
	uint8_t use_seconds = 1;
	
	configure_leds();
	timer1_init(TIMER_PRESCALER_1024, time_in_seconds, use_seconds, &switch_to_next_led_handler);
	
	sei();
}

uint8_t text[10];

int main(void)
{
	init();
	
    while (1);
}

