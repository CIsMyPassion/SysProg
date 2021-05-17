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

typedef void (* Interrupt_Handler)();

Interrupt_Handler interrupt0_handler;
Interrupt_Handler interrupt1_handler;

typedef struct 
{
	
} Interrupt_Config;

void init_interrupt(Interrupt_Handler isr0, Interrupt_Handler isr1)
{
	uint8_t eicra_byte = (1 << ISC01)  | (1 << ISC11);
	uint8_t eimsk_byte = (1 << INT0)   | (1 << INT1);
	uint8_t pind_byte =  (1 << PORTD2) | ( 1 <<PORTD3);
	
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