/*
 * interrupt.h
 *
 * Created: 15/05/2021 16:19:50
 *  Author: sjno
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>

typedef void (* Interrupt_Handler)();

Interrupt_Handler interrupt0_handler;
Interrupt_Handler interrupt1_handler;

void interrupt_init(Interrupt_Handler isr0, Interrupt_Handler isr1)
{
	interrupt0_handler = isr0;
	interrupt1_handler = isr1;

	uint8_t eicra_byte = (1 << ISC01)  | (1 << ISC11); // Interrupt trigger set to falling edge
	uint8_t eimsk_byte = (1 << INT0)   | (1 << INT1); // Turns on interrupt 0 and 1
	uint8_t pind_byte =  (1 << PORTD2) | ( 1 << PORTD3); // Activates internal pullup on the interrupt pin
	
	set_port(&EICRA, eicra_byte);
	set_port(&EIMSK, eimsk_byte);
	set_bit_for_port(&PORTD, pind_byte);
}

ISR (INT0_vect)
{
	interrupt0_handler(); // Execute handler for interrupt 0
}

ISR (INT1_vect)
{
	interrupt1_handler(); // Execute handler for interrupt 0
}

#endif /* INTERRUPT_H_ */