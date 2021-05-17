/*
 * Taster_Abfrage.c
 *
 * Created: 12/05/2021 21:48:24
 * Author : sjno
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "port_operations.h"
#include "timer.h"
#include "interrupt.h"

#define LED PORTB5
#define SLOW_BUTTON PORTD2
#define FAST_BUTTON PORTD3

#define INPUT_PORT PIND
#define OUTPUT_PORT PORTB

const uint16_t slow = 264 * 2;
const uint16_t fast = 440 * 2;
const uint16_t prescale = 256;

void slow_button_handler()
{
	timer_set_ocrn(slow);
}

void fast_button_handler()
{
	timer_set_ocrn(fast);
}

void switch_led_handler()
{
	toggle_bit_for_port(&PORTB, PORTB5);
}

inline void configure_output()
{
	uint8_t ddrb_byte = (1 << DDB5);
	set_port(&DDRB, ddrb_byte);
}

inline void init()
{
	configure_output();
	
	timer_init(prescale, fast, &switch_led_handler);
	interrupt_init(&slow_button_handler, &fast_button_handler);
	
	sei();
}


int main(void)
{
	init();
	
	while (1);
}



