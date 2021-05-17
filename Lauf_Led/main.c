/*
 * Lauf_Led.c
 *
 * Created: 12/05/2021 23:26:31
 * Author : sjno
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int lookup_index = 0;

const uint8_t lookup_table[] = {
	(1 << PORTB4) | (1 << PORTB0),
	(1 << PORTB4) | (1 << PORTB1),
	(1 << PORTB4) | (1 << PORTB2),
	(1 << PORTB4) | (1 << PORTB3),
	(1 << PORTB5) | (1 << PORTB0),
	(1 << PORTB5) | (1 << PORTB1),
	(1 << PORTB5) | (1 << PORTB2),
	(1 << PORTB5) | (1 << PORTB3),
	(1 << PORTB5) | (1 << PORTB3),
	(1 << PORTB5) | (1 << PORTB2),
	(1 << PORTB5) | (1 << PORTB1),
	(1 << PORTB5) | (1 << PORTB0),
	(1 << PORTB4) | (1 << PORTB3),
	(1 << PORTB4) | (1 << PORTB2),
	(1 << PORTB4) | (1 << PORTB1),
	(1 << PORTB4) | (1 << PORTB0)
};

inline void configure_leds()
{
	const uint8_t ddrb_byte = (1 << DDB0) | (1 << DDB1)
				| (1 << DDB2) | (1 << DDB3)
				| (1 << DDB4) | (1 << DDB5);
	
	DDRB = ddrb_byte;
	PORTB = lookup_table[0];
}

int main(void)
{
	configure_leds();
	
    while (1)
    {
		PORTB = lookup_table[lookup_index++ % 16];
		_delay_ms(200);
    }
}

