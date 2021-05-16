/*
 * Taster_Abfrage.c
 *
 * Created: 12/05/2021 21:48:24
 * Author : sjno
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "byte_operations.h"
#include "port_operations.h"
#include "timer_operations.h"

#define LED PORTB5
#define SLOW_BUTTON PORTD2
#define FAST_BUTTON PORTD3

#define INPUT_PORT PIND
#define OUTPUT_PORT PORTB

int slow = 264;
int fast = 440;
int prescale = 256;


inline void configure_input_output()
{
	uint8_t ddrb_byte = get_bitshifted_by(DDB5);
	set_port(&DDRB, ddrb_byte);
	clear_port(&DDRD);
}

inline void activate_pullups()
{
	uint8_t portd_byte = get_bitshifted_by(SLOW_BUTTON) | get_bitshifted_by(FAST_BUTTON);
	set_port(&PORTD, portd_byte);
}

inline void init_timer()
{
	OCR1A = calc_ocrn(fast,prescale);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);
}

inline void init()
{
	init_timer();
	configure_input_output();
	activate_pullups();
	
	// activate led on start
	set_bit_for_port(&OUTPUT_PORT, LED);	
}

inline void poll_buttons()
{
	if (read_inverted_bit_from_port(&INPUT_PORT, SLOW_BUTTON))
	{
		OCR1A = calc_ocrn(slow,prescale);
		set_bit_for_port(&OUTPUT_PORT, LED);
	}
	
	if(read_inverted_bit_from_port(&INPUT_PORT, FAST_BUTTON))
	{
		OCR1A = calc_ocrn(fast,prescale);
		clear_bit_for_port(&OUTPUT_PORT, LED);
	}
}

int main(void)
{
	init();
	
	while (1)
	{
		poll_buttons();
	}
}



