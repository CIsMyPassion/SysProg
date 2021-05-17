/*
 * analog.h
 *
 * Created: 16/05/2021 12:35:58
 *  Author: sjno
 */ 


#ifndef ANALOG_H_
#define ANALOG_H_

#include <avr/interrupt.h>

typedef void (* Analog_Read_Handler)(uint16_t);

static Analog_Read_Handler adc0_handler;
static Analog_Read_Handler adc1_handler;

void analog_init(Analog_Read_Handler adc0, Analog_Read_Handler adc1)
{
	adc0_handler = adc0; // Set the handler for the ADC0 channel
	adc1_handler = adc1; // Set the handler for the ADC1 channel
	
	ADMUX = 0; // Set the starting ADC channel to 0
	ADMUX |= (1 << REFS0); // Set the reference voltage to AVcc
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	
	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Enable the first ADC conversion
}

ISR(ADC_vect)
{
	uint8_t adc_number = ADMUX & 0x0F; // Isolate the ADC channel number from the ADMUX register
	
	uint16_t adc_value = ADCL; // Read the low 8 bit of the ADC
	adc_value |= (ADCH << 8); // Read the high 8 bit of the ADC
	
	switch (adc_number)
	{
		case 0:
			adc0_handler(adc_value); // Pass the ADC value to the handler function
			ADMUX++; //increment to the next ADC aka ADC1
			break;
		case 1:
			adc1_handler(adc_value); // Pass the ADC value to the handler function
			ADMUX &= 0xF8; //clear the last 4 bits to reset to ADC0
			break;
	}
	
	ADCSRA |= (1 << ADSC);    // Enable the next ADC conversion
	
}

#endif /* ANALOG_H_ */