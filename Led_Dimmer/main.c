/*
 * Led_Frequenzen.c
 *
 * Created: 12/05/2021 22:18:35
 * Author : sjno
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "byte_operations.h"
#include "port_operations.h"

inline void configure_output()
{
	set_port(&DDRD, get_bitshifted_by(DDD6));
	set_port(&OCR0A, 128);	// set PWM for 50% duty cycle

	uint8_t tccr0a_byte = get_bitshifted_by(COM0A1);	// none-inverting mode
	tccr0a_byte |= get_bitshifted_by(WGM01) | get_bitshifted_by(WGM00);		// fast PWM Mode
	set_port(&TCCR0A, tccr0a_byte);
	
	set_port(&TCCR0B, get_bitshifted_by(CS01));		// set prescaler to 8 and starts PWM
}

void init_trim(void)
{
	uint8_t admux_byte = get_bitshifted_by(REFS0);	// use AVcc as the reference 
	admux_byte |= get_bitshifted_by(ADLAR);			// Right adjust for 8 bit resolution
	set_port(&ADMUX, admux_byte);
	
	uint8_t adcsra_byte = get_bitshifted_by(ADPS2) | get_bitshifted_by(ADPS1) | get_bitshifted_by(ADPS0);	// 128 prescale for 16Mhz
	adcsra_byte |= get_bitshifted_by(ADATE);	// Set ADC Auto Trigger Enable
	adcsra_byte |= get_bitshifted_by(ADEN);		// Enable the ADC
	adcsra_byte |= get_bitshifted_by(ADIE);		// Enable Interrupts
	adcsra_byte |= get_bitshifted_by(ADSC);		// Start the ADC conversion
	set_port(&ADCSRA, adcsra_byte);
	
	clear_port(&ADCSRB);	// 0 for free running mode
	
	sei();
}

void init()
{
	configure_output();
	init_trim();
}

int main(void)
{
	
    init();
	
    while (1) 
    {
    }
}

ISR(ADC_vect)
{
	set_port(&OCR0A, ADCH);
}