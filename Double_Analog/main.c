/*
 * Double_Analog.c
 *
 * Created: 12/05/2021 22:43:04
 * Author : sjno
 */ 

#include <avr/io.h>
#include <stdlib.h>

#define F_CPU 16000000UL

#include <util/delay.h>

#include "analog.h"
#include "serial.h"

volatile uint16_t adc0_value;
volatile uint16_t adc1_value;

uint16_t adc0_printed_value;
uint16_t adc1_printed_value;

char adc0_string[7];
char adc1_string[7];

void analog_read_0(uint16_t adc_value)
{
	adc0_value = adc_value;
}

void analog_read_1(uint16_t adc_value)
{
	adc1_value = adc_value;
}

inline void initialize_strings()
{
	*adc0_string = '0';
	*(adc0_string + 1) = ':';
	
	*adc1_string = '1';
	*(adc1_string + 1) = ':';
}

inline void setup()
{
	serial_set_baud_rate(BAUD_9600);
	serial_init();
	
	analog_init(Analog_Res_10_Bit, &analog_read_0, &analog_read_1);
	
	sei();
	
	initialize_strings();
}

inline uint8_t check_and_correct_printed_values()
{
	uint8_t changed = 0;
	
	if (adc0_value != adc0_printed_value)
	{
		changed = 1;
		adc0_printed_value = adc0_value;
		
		itoa(adc0_value, adc0_string + 2, 10);
	}
	
	if (adc1_value != adc1_printed_value)
	{
		changed = 1;
		adc1_printed_value = adc1_value;
		
		itoa(adc1_value, adc1_string + 2, 10);
	}
	
	return changed;
}

inline void print_numbers()
{
	serial_clear();
	
	serial_send_string_new_line((uint8_t *) adc0_string);
	serial_send_string_new_line((uint8_t *) adc1_string);
}

int main(void)
{
	setup();
	
    while (1) 
    {
		uint8_t numbers_changed = check_and_correct_printed_values();
		
		if (numbers_changed)
			print_numbers();
		
		_delay_ms(60);
    }
}

