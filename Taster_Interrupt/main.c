/*
 * Taster_Interrupt.c
 *
 * Created: 12/05/2021 21:49:30
 * Author : sjno
 */ 

#include <avr/io.h>

#include "interrupt.h"
#include "port_operations.h"

void isr0()
{
	set_bit_for_port(&PORTB, PORTB5);
}

void isr1()
{
	clear_bit_for_port(&PORTB, PORTB5);
}

inline void configure_led()
{
	set_port(&DDRB, get_bitshifted_by(DDB5));
	set_port(&PORTB, get_bitshifted_by(PORTB5));
}

void init()
{
	init_interrupt(&isr0, &isr1);
	sei();
	
	configure_led();
}

int main(void)
{
	init();
	
	while (1)
	{
	}
}

