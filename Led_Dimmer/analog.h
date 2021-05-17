/*
 * anlaog.h
 *
 * Created: 17/05/2021 18:43:44
 *  Author: sjno
 */ 


#ifndef ANLAOG_H_
#define ANLAOG_H_

#include <avr/interrupt.h>

typedef void (* Analog_Read_Handler)(uint8_t);

static Analog_Read_Handler analog_read_handler;

void analog_init(Analog_Read_Handler handler)
{
	analog_read_handler = handler;
	
	uint8_t admux_byte = (1 << REFS0)	// use AVcc as the reference
				| (1 << ADLAR);			// Right adjust for 8 bit resolution
	set_port(&ADMUX, admux_byte);
	
	uint8_t adcsra_byte = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)	// 128 prescale for 16Mhz
				| (1 << ADATE)	// Set ADC Auto Trigger Enable
				| (1 << ADEN)		// Enable the ADC
				| (1 << ADIE)		// Enable Interrupts
				| (1 << ADSC);		// Start the ADC conversion
	set_port(&ADCSRA, adcsra_byte);
	
	clear_port(&ADCSRB);	// 0 for free running mode
	
	sei();
}

ISR(ADC_vect)
{
	analog_read_handler(ADCH);
}

#endif /* ANLAOG_H_ */