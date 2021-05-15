/*
 * Ampel.c
 *
 * Created: 12/05/2021 21:47:34
 * Author : sjno
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "byte_operations.h"
#include "port_operations.h"

enum light_states {
	green = 1 << PORTB4,
	yellow = 1 << PORTB3,
	red = 1 << PORTB2,
	red_yellow = yellow | red
} light_state;

void init()
{
	light_state = red_yellow;
	
	uint8_t ddrb_byte = get_bitshifted_by(DDB2)
			| get_bitshifted_by(DDB3)
			| get_bitshifted_by(DDB4);
	
	set_port(&DDRB, ddrb_byte);
	clear_port(&PORTB);
}

inline void switch_lights_for_state()
{
	set_port(&PORTB, light_state);
}

void delay_for_state()
{
	switch (light_state)
	{
		case green:
		case red:
			_delay_ms(1000);
			break;
		case yellow:
		case red_yellow:
			_delay_ms(200);
			break;
	}
}

void set_new_state()
{
	switch (light_state)
	{
		case green:
			light_state = yellow;
			break;
		case yellow:
			light_state = red;
			break;
		case red:
			light_state = red_yellow;
			break;
		case red_yellow:
			light_state = green;
			break;
	}
}

int main(void)
{
	init();
	
	while (1)
	{
		switch_lights_for_state();
		delay_for_state();
		set_new_state();
	}
}