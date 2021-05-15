/*
 * interrupt.h
 *
 * Created: 15/05/2021 16:19:50
 *  Author: sjno
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>

#include "port_operations.h"
#include "byte_operations.h"

typedef void (* Interrupt_Handler)();

Interrupt_Handler interrupt0_handler;
Interrupt_Handler interrupt1_handler;

typedef struct 
{
	
} Interrupt_Config;

void init_interrupt(Interrupt_Handler isr0, Interrupt_Handler isr1)
{
	uint8_t eicra_byte = get_bitshifted_by(ISC01) | get_bitshifted_by(ISC11);
	uint8_t eimsk_byte = get_bitshifted_by(INT0) | get_bitshifted_by(INT1);
	uint8_t pind_byte = get_bitshifted_by(PORTD2) | get_bitshifted_by(PORTD3);
	
	set_port(&EICRA, eicra_byte);
	set_port(&EIMSK, eimsk_byte);
	PORTD |= pind_byte;
	
	interrupt0_handler = isr0;
	interrupt1_handler = isr1;
}

ISR (INT0_vect)
{
	interrupt0_handler();
}

ISR (INT1_vect)
{
	interrupt1_handler();
}

#endif /* INTERRUPT_H_ */